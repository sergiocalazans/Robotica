#include "arduino_secrets.h"

/****************************************************/
/* Aula 04 - SemÃ¡foro Inteligente com IR.           */
/* ProgramaÃ§Ã£o do semÃ¡foro inteligente com sensor IR*/
/* (InfraVermelho). Seu funcionamento consiste em   */
/* alterar seu modo de operaÃ§Ã£o assim que o sensor  */
/* detectar a presenÃ§a de um pedestre.              */
/* Utilizamos uma funÃ§Ã£o nativa do Arduino IDE, a   */
/* funÃ§Ã£o de interrupÃ§Ã£o (attachInterrupt). Para    */
/* saber mais sobre a funÃ§Ã£o acesse:                */
/* https://www.arduino.cc/reference/pt/language/functions/external-interrupts/attachinterrupt/ */
/****************************************************/

/* DefiniÃ§Ãµes dos pinos para os LEDs e sensor IR.   */
#define PIN_SENSOR 2
#define PIN_LED_VERDE_CAR 3
#define PIN_LED_AMARELO_CAR 4
#define PIN_LED_VERMELHO_CAR 5
#define PIN_LED_VERDE_PED 6
#define PIN_LED_VERMELHO_PED 7

/* VariÃ¡vel que seleciona o modo de operaÃ§Ã£o do     */
/* semÃ¡foro 0: Modo aberto para carros e 1: Modo    */
/* travessia de pedestres.                          */
int modo = 0;

void setup() {
  /* Configura o pino do sensor como ENTRADA.       */
  pinMode(PIN_SENSOR, INPUT);
  /* Loop para configurar os pinos 3 a 7 como SAÃDA.*/
  for (int i = 3; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  /* Ativa a funÃ§Ã£o de interrupÃ§Ã£o no pino que o      */
  /* sensor estÃ¡ conectado.                           */
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), sensorAcionado, FALLING);
}

void loop() {
  /* Switch com dois modos de operaÃ§Ã£o: modo aberto para 
    carros e modo travessia de pedestre. Enquanto o sensor
    nÃ£o detectar um pedestre, o modo de operaÃ§Ã£o permanece
    em 0, ou seja, aberto para a passagem dos carros. Caso o
    sensor detecte um pedestre, a funÃ§Ã£o attachInterrupt irÃ¡
    imediatamente alterar o modo de operaÃ§Ã£o para 1, ou seja,
    entrarÃ¡ no modo de travessia dos pedestres. */
  switch (modo) {
    case 0:
      modocarros();
      break;
    case 1:
      travessia();
      break;
  }
}

/* ApÃ³s o sensor detectar o pedestre, serÃ¡ executada essa*/
/* funÃ§Ã£o, ela altera o modo de operaÃ§Ã£o do semÃ¡foro.    */

void sensorAcionado() {
  modo = 1;
}
/* FunÃ§Ã£o que ativa  o modo "Travessia de pedestres"     */
void travessia() {
  /* Aguarda 1 segundo apÃ³s o sensor detectar o pedestre */
  delay(1000);
  /* Aciona o amarelo do semÃ¡foro dos carros             */
  digitalWrite(PIN_LED_VERDE_CAR, LOW);
  digitalWrite(PIN_LED_AMARELO_CAR, HIGH);
  delay(3000);
  /* Abre o semÃ¡foro de pedestres.                       */
  digitalWrite(PIN_LED_VERDE_PED, HIGH);
  digitalWrite(PIN_LED_VERMELHO_PED, LOW);
  digitalWrite(PIN_LED_AMARELO_CAR, LOW);
  digitalWrite(PIN_LED_VERMELHO_CAR, HIGH);
  delay(5000);
  /* Apaga o verde dos pedestres e comeÃ§a a piscar 
   *  o vermelho, indicando que o tempo de travessia 
   *  estÃ¡ acabando.                 
   */
  digitalWrite(PIN_LED_VERDE_PED, LOW);
  for (int i = 0; i <= 5; i++)
  {
    digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
    delay(300);
    digitalWrite(PIN_LED_VERMELHO_PED, LOW);
    delay(300);
  }
  /* ApÃ³s a travessia de pedestre, altera para o modo 
   * de passagem de carros: 0 */
  modo = 0; 
}
/* FunÃ§Ã£o que ativa os LEDs para o modo "Aberto para carros" */
void modocarros() {
  digitalWrite(PIN_LED_VERDE_PED, LOW);
  digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
  digitalWrite(PIN_LED_VERDE_CAR, HIGH);
  digitalWrite(PIN_LED_AMARELO_CAR, LOW);
  digitalWrite(PIN_LED_VERMELHO_CAR, LOW);
}
