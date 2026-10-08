# Robótica

Projetos e atividades de robótica desenvolvidos durante o 2º e o 3º ano do Ensino Médio.

Este repositório reúne sketches exportadas do Arduino Cloud Editor e usadas em aulas, estudos e experimentos práticos com Arduino, sensores, LEDs, motores, displays e comunicação. A organização foi mantida por pasta para preservar cada projeto como uma unidade independente de estudo.

## Contexto

Parte dos códigos e propostas tem origem ou inspiração nos materiais da [Robótica Paraná](https://www.educacao.pr.gov.br/programa/robotica-parana), iniciativa da Secretaria de Estado da Educação do Paraná voltada a estudantes do Ensino Fundamental e Médio da rede estadual. O programa trabalha aulas e projetos de robótica para desenvolver criatividade, autonomia, cooperação e resolução de problemas com tecnologia.

As aulas de Robótica Educacional do Ensino Médio são organizadas em módulos por série, com desenvolvimento progressivo de projetos usando o kit de robótica e a plataforma Arduino. A página da [Escola Digital - Robótica Educacional](https://aluno.escoladigital.pr.gov.br/robotica/aulas/educacional) lista os módulos do Ensino Médio, e a área de [projetos da Robótica Paraná](https://aluno.escoladigital.pr.gov.br/robotica/projetos) reúne materiais como semáforos com Arduino, irrigador automático, fechadura wireless e outros experimentos.

Também há códigos criados ou adaptados por mim durante as aulas, com foco em testar componentes, entender lógica de programação embarcada e montar pequenos protótipos funcionais.

## Projetos

| Pasta | Descrição |
| --- | --- |
| `Arco_Iris` | Efeito visual com LEDs, explorando cores e temporização. |
| `Carrinho_Codigo_Aleatorio` | Controle de carrinho com movimentos aleatórios. |
| `Carrinho_Codigo_Constante` | Controle de carrinho com comportamento constante. |
| `Chassi_2wd` | Projeto com chassi 2WD e controle de motores. |
| `codigo_morse` | Introdução à lógica de código Morse com sinais luminosos/sonoros. |
| `codigo_morse_2` | Variação do projeto de código Morse. |
| `codigo_morse_frase` | Codificação de frases em Morse. |
| `codigo_morse_sensor` | Integração de código Morse com leitura de sensor. |
| `codigo_morse_sensor_2` | Segunda versão da integração entre Morse e sensor. |
| `Fechadura_Eletronica` | Fechadura com senha e controle de acesso. |
| `LED_RGB` | Controle de LED RGB e mistura de cores. |
| `Matriz_LED_8x8` | Experimentos com matriz de LEDs 8x8. |
| `Robo_Seguidor_de_Linha_Ponte_H` | Robô seguidor de linha usando ponte H. |
| `Robo_Sumo_Ponte_H` | Robô sumô com controle de motores por ponte H. |
| `Semaforo_Inteligente_com_IR` | Semáforo com sensor infravermelho. |
| `semaforo_IR_codigo_morse` | Semáforo com sensor IR integrado a lógica de Morse. |
| `semaforo_pedestres` | Simulação de semáforo para pedestres. |
| `Sensor_de_Chuva` | Medição de intensidade de chuva com indicação por LEDs. |
| `Sensor_de_Distancia` | Leitura de distância com sensor ultrassônico. |
| `Sensor_de_Estacionamento` | Sensor de estacionamento com alerta por proximidade. |
| `Sensor_Umidade_Solo` | Leitura de umidade do solo. |
| `servidor_web_tech_roots` | Monitoramento com ESP8266, servidor web, DHT11, LCD e umidade do solo. |
| `tech_roots` | Monitoramento e envio de dados usando DHT11, umidade do solo e nRF24L01. |
| `umidade_solo_makerhero` | Experimento de umidade do solo baseado em material MakerHero. |

## Como usar

1. Abra a pasta do projeto desejado no Arduino IDE ou importe a sketch no Arduino Cloud Editor.
2. Confira a placa e bibliotecas indicadas no arquivo `sketch.json`, quando disponível.
3. Monte o circuito correspondente ao projeto.
4. Compile e envie o código para a placa.

Algumas sketches incluem `#include "arduino_secrets.h"` porque foram exportadas do Arduino Cloud. Arquivos com segredos locais não são versionados. Caso um projeto dependa de rede Wi-Fi ou outra credencial, crie esse arquivo localmente e defina os valores necessários, por exemplo:

```cpp
#define SECRET_SSID "nome-da-rede"
#define SECRET_PASS "senha-da-rede"
```

## Objetivo do repositório

Este repositório funciona como portfólio escolar e registro de aprendizagem. Ele documenta a evolução dos estudos em robótica educacional, programação em Arduino e prototipagem, reunindo projetos que conectam lógica de programação, eletrônica básica e resolução prática de problemas.
