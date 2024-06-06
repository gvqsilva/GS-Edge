<h1 align="Center">Projeto "Inovação Azul" - Monitoramento da Saúde dos Oceanosb Descrição</h1>

# Índice
* [Descrição do Projeto](#descricao)
* [O problema](#Problema)
* [Solução proposta](#solucao)
* [Componentes utilizados](#componentes)
* [Funcionamento](#funcionamento)
* [Como usar](#como-usar)
* [Vídeo](#video)
* [Código](#codigo)
* [Acesso ao simulador](#simulador)
* [Autores](#autores)


<h2 id="Descricao">Descrição do projeto</h2>
<p>Este projeto foi desenvolvido como parte do Desafio de "Inovação Azul" 2024, que visa incentivar a criação de soluções para promover uma gestão sustentável dos oceanos.</p>
<p>Nosso projeto se concentra em capturar dados sobre a saúde dos oceanos e criar visualizações intuitivas para informar as populações costeiras e as empresas marítimas sobre a condição dos oceanos.</p>

<h2 id="Problema">Problema</h2>
<p>Os oceanos estão enfrentando sérios desafios devido à poluição, mudanças climáticas e outras atividades humanas. No entanto, as comunidades costeiras e as empresas que dependem dos oceanos muitas vezes carecem de informações acessíveis e compreensíveis sobre a saúde dos oceanos e os impactos das atividades humanas.</p>

<h2 id="Solucao">Solução Proposta</h2>
<p>Nossa solução consiste em um sistema de monitoramento da saúde dos oceanos, utilizando a plataforma Arduino e sensores para capturar dados relevantes, como temperatura da água, pH e turbidez. Esses dados são processados e exibidos em tempo real por meio de um LCD, tornando as informações facilmente acessíveis para as comunidades e empresas interessadas.</p>

<h2 id="Componentes">Componentes Utilizados📖</h2>
  <ul>
    <li>Arduino UNO;</li>
    <li>Sensor de Temperatura e Umidade (DHT22);</li>
    <li>Display lcd I2c;</li>
    <li>Potenciometro (para simular um sensor de turbidez, ver se a água está turva);</li>
    <li>Potenciometro (para simular um sensor de pH);</li>
    <li>RTC DS1307 (para o armazenamento de dados);</li>
    <li>Componentes eletrônicos diversos (fios, etc.).</li>
  </ul>

<h2 id="funcionamento">Funcionamento🔨</h2>
<p>O sistema captura dados dos sensores a intervalos regulares e exibe as leituras em tempo real no LCD. Além disso, os dados são registrados com carimbo de data/hora para análise posterior. Se os valores medidos estiverem fora dos limites predefinidos, o sistema os registra e alerta os usuários.</p>
<p align = "center">
<img loading="lazy" width="500px" src = 'https://github.com/gvqsilva/GS-Edge/assets/110639916/b1daa2f9-5d97-439c-a6d6-cb2a2e02b0c7'/>
</p>
<p align = "center">
Figura 1 - Imagem do prototipo
</p>

<h2 id="como usar">Como Usar📑</h2>

  `Primeiro`: Monte os componentes de acordo com o esquema de conexões fornecido.
  
  `Segundo`: Carregue o código Arduino no Arduino Uno.
  
  `Terceiro`: Conecte a alimentação e os sensores de acordo com as instruções.
  
  `Quarto`: Os dados serão exibidos no LCD e também serão enviados para o monitor serial.
  
  `Quinto`: Resultados Esperados
  
  `Sexto`: Esperamos que essa solução forneça às comunidades costeiras e às empresas marítimas informações valiosas sobre a saúde dos oceanos. Com acesso a dados em tempo real e visualizações claras, as pessoas podem tomar decisões mais informadas e contribuir para a preservação dos oceanos.

<h2 id="video">Vídeo</h2>


<h2 id="codigo">Codigo</h2>
https://github.com/gvqsilva/GS-Edge/blob/main/codigo-do-projeto/sketch_jun6a.ino

<h2 id="Simulador">Acesso ao simulador</h2>
https://wokwi.com/projects/399959015744618497

<h2 id="Autores">Autores</h2>

<div align="center">
  
| [<img loading="lazy" src="https://github.com/gvqsilva/CP2-Edge/assets/110639916/d022ed18-0057-4944-9e00-db796c6d2e45" width=115><br><sub>Gabriel Vasquez</sub>](https://github.com/gvqsilva)  |  [<img loading="lazy" src="https://github.com/gvqsilva/CP2-Edge/assets/110639916/4bb3084d-d1ff-4b49-ba37-96c8046f6e14" width=115><br><sub>Gustavo Oliveira</sub>](https://github.com/Gusta346) |
| :---: | :---: |

</div>
