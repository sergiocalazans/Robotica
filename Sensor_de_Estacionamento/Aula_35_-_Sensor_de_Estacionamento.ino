#include "arduino_secrets.h"

/*******************************************************/
/* Aula 35 - Sensor de Estacionamento                  */
/* ProgramaÃ§Ã£o: Nesta aula, programamos o mÃ³dulo sensor*/
/* ultrassÃ´nico HC - SR04 para simular um sensor de    */
/* estacionamento. Conforme um obstÃ¡culo se aproxima   */
/* do sensor um aviso sonoro serÃ¡ emitido atravÃ©s do   */
/* buzzer, aumentando a intensidade dos bips quanto    */
/* menor a distÃ¢ncia.                                  */
/* Links para obtenÃ§Ã£o da biblioteca by Erick SimÃµes   */
/* http://librarymanager/All#minimalist#Ultrasonic     */
/* https://github.com/ErickSimoes/Ultrasonic           */
/*******************************************************/

#include <Ultrasonic.h>

int pino_Trig = 3,pino_Echo = 4, distancia;

Ultrasonic Sensor(pino_Trig, pino_Echo);

float pino_buzzer = 2, frequencia = 3500;

void setup() {
  pinMode(pino_buzzer, OUTPUT);
}//setup

void loop() {
 
  distancia = Sensor.read();

  if (distancia < 80 && distancia > 50) {
    tone(pino_buzzer, frequencia, 100);
    delay(1000);
  }//if

  if (distancia < 50 && distancia > 30) {
    tone(pino_buzzer, frequencia, 100);
    delay(700);
  }//if

  if (distancia < 30 && distancia > 20) {
    tone(pino_buzzer, frequencia, 100);
    delay(300);
  }//if
 
  if (distancia < 20 && distancia > 10) {
    tone(pino_buzzer, frequencia, 100);
    delay(150);
  }//if
 
  if (distancia < 10) {
    tone(pino_buzzer, frequencia);
  }//if

}//loop
