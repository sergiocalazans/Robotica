#include "arduino_secrets.h"

/*******************************************************/
/* Aula 34 - Sensor de distÃ¢ncia                       */
/* ProgramaÃ§Ã£o: Nesta aula, programamos o mÃ³dulo sensor*/
/* ultrassÃ´nico HC - SR04 para realizar a medida da    */
/* distÃ¢ncia de obstÃ¡culos a sua frente. A distÃ¢ncia   */
/* Ã© acompanhada atravÃ©s do monitor serial do software */
/* Arduino IDE.                                        */ 
/* Links para obtenÃ§Ã£o da biblioteca by Erick SimÃµes   */
/* http://librarymanager/All#minimalist#Ultrasonic     */
/* https://github.com/ErickSimoes/Ultrasonic           */
/*******************************************************/

/* Inclui a Biblioteca de controle do sensor.          */
#include <Ultrasonic.h>
/* DefiniÃ§Ã£o dos pinos para o sensor.                  */
float pino_Trig = 3;
float pino_Echo = ;
/* Cria o objeto Sensor para realizar a leitura.       */
Ultrasonic Sensor(pino_Trig, pino_Echo);
/* VariÃ¡vel que armazenarÃ¡ as medidas.                 */
float distancia;
void setup() {
/* Inicia a comunicaÃ§Ã£o serial na velocidade 9600.     */
Serial.begin(9600);
}
void loop() {
/* Realiza a mediÃ§Ã£o e armazena na variÃ¡vel âdistanciaâ */
distancia = Sensor.read();
/* Imprime no Monitor Serial os valores das medidas a   */
/* cada 0,5 segundos.                                   */
Serial.print("DistÃ¢ncia: ");
Serial.print(distancia);
Serial.println("cm");
delay(500);
}
