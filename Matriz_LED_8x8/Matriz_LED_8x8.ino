#include "arduino_secrets.h"

/************************************************************/
/* Aula 06 - Matriz de LED 8x8                              */
/* ProgramaÃ§Ã£o do MÃ³dulo Matriz de LED 8x8.                 */
/* Ao transferir o cÃ³digo abaixo para seu Arduino, serÃ¡     */
/* apresentado no Display, uma contagem de 0 a 9 seguido da */
/* frase "Robotica Parana" com efeito de rolagem.           */
/* Links para obtenÃ§Ã£o da biblioteca by Daniel Alvarez      */
/* http://librarymanager/All#MatrizLed                      */
/* https://github.com/danidask/MatrizLed                    */
/************************************************************/

#include <MatrizLed.h>
/* Cria o objeto Display para controlar a matriz de LED.    */
MatrizLed Display;
void setup() {
  /* Inicia o Display: (DIN, CLK, CS e o nÂº de displays     */
  /*conectados em sÃ©rie.                                    */
  Display.begin(8, 10, 9, 1);
  /* Define o brilho dos LEDs na matriz para o valor 10.    */
  /* (A intensidade varia de 0 a 15).                       */
  Display.setIntensidad(15);
}
void loop() {

  /* Chama a funÃ§Ã£o que realiza a contagem de 0 a 9.        */
  contador();

  /* Exibe a frase com efeito Rolagem no Display. A rolagem */
  /* estÃ¡ definida num intervalo de 80 milissegundos.       */
  Display.escribirFraseScroll("BET", 80);
  
}
/* FunÃ§Ã£o que exibe a contagem de 0 a 9.                    */
void contador() {
  for (int i = 9; i >= 0; i--) {
    Display.escribirCifra(i);
    delay(500);
    Display.borrar();
  }
}
