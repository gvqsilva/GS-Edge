#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <EEPROM.h>
#include <RTClib.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define PH_PIN A0
#define TURBIDITY_PIN A1
#define LOG_OPTION 1     // Opção para ativar a leitura do log
#define SERIAL_OPTION 1  // Opção de comunicação serial: 0 para desligado, 1 para ligado
#define UTC_OFFSET -3    // Ajuste de fuso horário para UTC-3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;

// Configurações da EEPROM
const int maxRecords = 100;
const int recordSize = 12; // Tamanho de cada registro em bytes
int startAddress = 0;
int endAddress = maxRecords * recordSize;
int currentAddress = 0;

float trigger_t_min = 20.0; // Exemplo: valor mínimo de temperatura
float trigger_t_max = 30.0; // Exemplo: valor máximo de temperatura
float trigger_ph_min = 6.0; // Exemplo: valor mínimo de pH
float trigger_ph_max = 8.0; // Exemplo: valor máximo de pH
float trigger_turb_min = 0.0; // Exemplo: valor mínimo de turbidez
float trigger_turb_max = 1000.0; // Exemplo: valor máximo de turbidez

unsigned long previousMillis = 0; // Armazena a última vez que a leitura foi feita
const long interval = 5000; // Intervalo de tempo entre as leituras (5 segundos)

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    dht.begin();
    pinMode(PH_PIN, INPUT);
    pinMode(TURBIDITY_PIN, INPUT);
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    if (!rtc.begin()) {
        Serial.println("RTC não encontrado!");
        while (1);
    }
    if (!rtc.isrunning()) {
        Serial.println("RTC não está funcionando, ajustando a data e hora...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    EEPROM.begin();
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Leitura dos sensores
        float temperature = dht.readTemperature();
        float phValue = analogRead(PH_PIN) * (14.0 / 1023.0);
        float turbidityValue = analogRead(TURBIDITY_PIN) * (1000.0 / 1023.0);

        // Obtenção do tempo atual
        DateTime now = rtc.now();
        int offsetSeconds = UTC_OFFSET * 3600;
        now = now.unixtime() + offsetSeconds;
        DateTime adjustedTime = DateTime(now);

        // Verificação e registro de dados fora dos limites
        if (LOG_OPTION) get_log();
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
        if (temperature < trigger_t_min || temperature > trigger_t_max || 
            phValue < trigger_ph_min || phValue > trigger_ph_max || 
            turbidityValue < trigger_turb_min || turbidityValue > trigger_turb_max) {
            int tempInt = (int)(temperature * 100);
            int phInt = (int)(phValue * 100);
            int turbInt = (int)(turbidityValue * 100);
            EEPROM.put(currentAddress, now.unixtime());
            EEPROM.put(currentAddress + 4, tempInt);
            EEPROM.put(currentAddress + 6, phInt);
            EEPROM.put(currentAddress + 8, turbInt);
            getNextAddress();
        }

        // Impressão dos dados no monitor serial
        if (SERIAL_OPTION) {
            Serial.print(adjustedTime.day());
            Serial.print("/");
            Serial.print(adjustedTime.month());
            Serial.print("/");
            Serial.print(adjustedTime.year());
            Serial.print(" ");
            Serial.print(adjustedTime.hour() < 10 ? "0" : ""); 
            Serial.print(adjustedTime.hour());
            Serial.print(":");
            Serial.print(adjustedTime.minute() < 10 ? "0" : ""); 
            Serial.print(adjustedTime.minute());
            Serial.print(":");
            Serial.print(adjustedTime.second() < 10 ? "0" : ""); 
            Serial.print(adjustedTime.second());
            Serial.print(" Temp: ");
            Serial.print(temperature);
            Serial.print("°C   pH: ");
            Serial.print(phValue);
            Serial.print("   Turb: ");
            Serial.print(turbidityValue);
            Serial.print("\n");
        }

        // Exibição dos dados no LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("pH:");
        lcd.print(phValue);
        lcd.print(" Turb:");
        lcd.print(turbidityValue);
    }
}

void getNextAddress() {
    currentAddress += recordSize;
    if (currentAddress >= endAddress) {
        currentAddress = 0;
    }
}

void get_log() {
    Serial.println("Data stored in EEPROM:");
    Serial.println("Timestamp\t\tTemperature\tpH\tTurbidity");

    for (int address = startAddress; address < endAddress; address += recordSize) {
        long timeStamp;
        int tempInt, phInt, turbInt;

        EEPROM.get(address, timeStamp);
        EEPROM.get(address + 4, tempInt);
        EEPROM.get(address + 6, phInt);
        EEPROM.get(address + 8, turbInt);

        if (timeStamp != 0xFFFFFFFF) {
            DateTime dt = DateTime(timeStamp);
            Serial.print(dt.timestamp(DateTime::TIMESTAMP_FULL));
            Serial.print("\t");
            Serial.print(tempInt / 100.0);
            Serial.print(" C\t\t");
            Serial.print(phInt / 100.0);
            Serial.print("\t");
            Serial.print(turbInt / 100.0);
            Serial.print("\n");
        }
    }
}