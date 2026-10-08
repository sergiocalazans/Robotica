#include "arduino_secrets.h"

/********************************************************/
/* Aula 32 - Kit Chassi 2WD com ponte H - RobÃ´ */
/* ProgramaÃ§Ã£o: Nesta programaÃ§Ã£o controlamos dois */
/* motores DC utilizando a placa Motor Driver L298N. */
/* para mover o robÃ´ em todas as direÃ§Ãµes possÃ­veis. */
/* Links para obtenÃ§Ã£o da biblioteca by Andrea Lombardo */
/* http://librarymanager/All#L298N#EASY */
/* https://github.com/AndreaLombardo/L298N */
/********************************************************/
/* Inclui a Biblioteca para controle da ponte H. */
#include <L298NX2.h>
#define ENA 10 // ENA precisa estar em uma porta PWM
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5 // ENB precisa estar em uma porta PWM
/* Criamos um objeto de controle dos motores. */
L298NX2 motores(ENA, IN1, IN2, ENB, IN3, IN4);
void setup() {
  /* Inicia com os motores parados. */
  motores.stop();
}
void loop() {
  /* Define a velocidade em 255 (0-255). */
  motores.setSpeed(255); // Velocidade mÃ¡xima
  
  /* Chama a funÃ§Ã£o frente por 1000 milissegundos */
  frente(1000);
  /* Pausa de meio segundo */
  delay(500);
  /* Chama a funÃ§Ã£o rÃ© por 1000 milissegundos */
  re(1000);
  /* Pausa de meio segundo */
  delay(500);
  /* Chama a funÃ§Ã£o girar em torno do centro no sentido */
  /* antihorÃ¡rio por 1000 milissegundos */
  giro_centro_antihorario(1000);
  /* Pausa de meio segundo */
  delay(500);
  /* Chama a funÃ§Ã£o girar em torno do centro no sentido */
  /* horÃ¡rio por 1000 milissegundos */
  giro_centro_horario(1000);
  /* Pausa de meio segundo */
  delay(500);
  /* Chama a funÃ§Ã£o girar em torno da roda no sentido */
  /* antihorÃ¡rio por 1000 milissegundos */
  giro_roda_antihorario(1000);
  /* Pausa de meio segundo */
  delay(500);
  /* Chama a funÃ§Ã£o girar em torno da roda no sentido */
  /* horÃ¡rio por 1000 milissegundos */
  giro_roda_horario(1000);
  /* Pausa de cinco segundos */
  delay(5000);
}
/* FunÃ§Ã£o que move para frente pelo tempo definido */
void frente(int tempo) {
  motores.forward();
  delay(tempo);
  motores.stop();
}
/* FunÃ§Ã£o que move para trÃ¡s pelo tempo definido */
void re(int tempo) {
  motores.backward();
  delay(tempo);
  motores.stop();
}
/* FunÃ§Ã£o que gira em torno do centro no sentido */
/* antihorÃ¡rio pelo tempo definido */
void giro_centro_antihorario(int tempo) {
  motores.backwardA();
  motores.forwardB();
  delay(tempo);
  motores.stop();
}
/* FunÃ§Ã£o que gira em torno do centro no sentido */
/* horÃ¡rio pelo tempo definido */
void giro_centro_horario(int tempo) {
  motores.backwardB();
  motores.forwardA();
  delay(tempo);
  motores.stop();
}
/* FunÃ§Ã£o que gira em torno da roda no sentido */

/* antihorÃ¡rio pelo tempo definido */
void giro_roda_antihorario(int tempo) {
  motores.forwardB();
  delay(tempo);
  motores.stop();
}
/* FunÃ§Ã£o que gira em torno da roda no sentido */
/* horÃ¡rio pelo tempo definido */
void giro_roda_horario(int tempo) {
  motores.forwardA();
  delay(tempo);
  motores.stop();
}
