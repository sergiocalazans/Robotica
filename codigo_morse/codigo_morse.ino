#include "arduino_secrets.h"

/* Programa: CÃ³digo Morse */
/* Definindo os pinos do Buzzer, botÃ£o e LED */
int buzzer = 2;
int botao = 3;
int LED = 4;
void setup()
{
/* Define os pinos do LED e Buzzer como saÃ­da */
pinMode(buzzer, OUTPUT);
pinMode(LED, OUTPUT);
 /* Define o pino do botÃ£o como entrada e ativa o resistor
interno */
pinMode(botao, INPUT_PULLUP);
}
void loop()
{ /* Verifica se o botÃ£o estÃ¡ pressionado e entÃ£o liga o LED e
emite o som */
if (digitalRead(botao) == LOW) {
 digitalWrite(LED, HIGH);
 tone(buzzer, 800);
}
/* SenÃ£o desligue o LED e pare o som */
else {
 digitalWrite(LED, LOW);
 noTone(buzzer);
}
}