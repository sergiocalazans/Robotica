#include "arduino_secrets.h"

/***************************************************************/
/* Aula 17 - Fechadura EletrÃ´nica                              */
/* ProgramaÃ§Ã£o da Fechadura EletrÃ´nica.                        */
/* Ao transferir o cÃ³digo abaixo para seu Arduino, vocÃªpoderÃ¡  */
/* utilizar o protÃ³tipo da fechadura eletrÃ´nica do seguinte    */
/* modo: ao digitar uma sequÃªncia de caracteres, atravÃ©s do    */
/* teclado matricial de membrana, o Arduino irÃ¡ comparar com a */
/* senha definida na linha 26 deste sketch.                    */
/* Caso a senha nÃ£o coincidir, a fechadura serÃ¡ mantida        */
/* trancada (LED Vermelho aceso e Servo Motor na posiÃ§Ã£o 90Âº), */
/* caso os caracteres coincidam, a fechadura serÃ¡ destrancada  */
/* (LED Verde aceso e Servo Motor na posiÃ§Ã£o 180Âº). Para       */
/* trancar novamente, basta pressionar as teclas * ou #.       */
/* O estado da fechadura tambÃ©m pode ser acompanhadao atravÃ©s  */
/* do Monitor Serial do Arduino IDE.                           */
/* Links para obtenÃ§Ã£o da biblioteca by Comunity https://...   */
/* http://librarymanager/All#keypad#upon                       */
/* https://github.com/Chris--A/keypad                          */
/***************************************************************/
#include <Keypad.h>
/* Inclui a bliblioteca de controle do Servo Motor.         */
#include<Servo.h>
/* Cria o objeto de controle do Servo Motor.                */
Servo servo;
/* Define a senha para destravar a fechadura.               */
char* password = "123";
/* Quantidade de caracteres que a senha possui.             */
int caracteres = 3;
/* Define os pinos dos LEDs e Servo Motor.                  */
#define ledVermelho 12
#define ledVerde 11
#define Pin_Servo 10
/* VariÃ¡vel de controle.                                    */
int posicao = 0;
/* Define o nÃºmero de linhas e colunas do teclado matricial */
/* de membrana.                                             */
#define qtdLinhas 4
#define qtdColunas 4
/* ConstruÃ§Ã£o da matriz de caracteres.                      */
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
/* Define os pinos de controle de linhas e colunas.         */
byte PinosqtdLinhas[qtdLinhas] = {9, 8, 7, 6};
byte PinosqtdColunas[qtdColunas] = {5, 4, 3, 2};
/* Cria o objeto de controle do teclado.                    */
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);
void setup() {
  /* Configura os pinos dos LEDs como saÃ­da.                */
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  /* EndereÃ§a o objeto de controle ao pino definido para    */
  /* controle do Servo Motor.                               */
  servo.attach(Pin_Servo);
  /* Inicia a comunicaÃ§Ã£o Serial em 9600 bauds.             */
  Serial.begin(9600);
  /* Imprime a frase no Monitor Serial.                     */
  Serial.println("Entre com a senha...");
  /* Pula uma linha no Monitor Serial.                      */
  Serial.println();
  /* Inicia com a fechadura trancada */
  trancada();
}
void loop() {
  /* Armazena na variÃ¡vel key a tecla pressionada.          */
  char key = meuteclado.getKey();
  /* Se a tecla pressionada for "*" ou "#" reinicia a       */
  /* tentativa com a fechadura trancada.                    */
  if (key == '*' || key == '#') {
    posicao = 0;
    trancada();
  }
  /* Se as teclas pressionadas coincidirem com a senha,     */
  /* destranque a fechadura.                                */
  if (key == password[posicao]) {
    posicao ++;
  }
  if (posicao == caracteres) {
    destrancada();
  }
  /* Pequena pausa para retomar a leitura.                  */
  delay(100);
}
/* FunÃ§Ã£o que mantÃ©m a fechadura trancada.                  */
void trancada()
{
  /* LED Vermelho acende.                                   */
  digitalWrite(ledVermelho, HIGH);
  /* LED Verde apaga.                                       */
  digitalWrite(ledVerde, LOW);
  /* Servo na posiÃ§Ã£o trancada.                             */
  servo.write(90);
  /* Imprime a palavra no Monitor Serial.                   */
  Serial.println("TRANCADA");
}
/* FunÃ§Ã£o que mantÃ©m a fechadura destrancada.               */
void destrancada()
{
  /* LED Verde acende.                                      */
  digitalWrite(ledVerde, HIGH);
  /* LED Vermelho apaga.                                    */
  digitalWrite(ledVermelho, LOW);
  /* Servo na posiÃ§Ã£o destrancada.                          */
  servo.write(180);
  /* Imprime a palavra no Monitor Serial.                   */
  Serial.println("ABERTA");
}
