#include "arduino_secrets.h"

#include <AFMotor.h> /* Inclui a Biblioteca AFMotor.h */
AF_DCMotor motor2(2); /* Defi ne motor2 como posiÃ§Ã£o 2 de
controle para motor */
AF_DCMotor motor3(3); /* Defi ne motor3 como posiÃ§Ã£o 3 de
controle para motor */
void setup() {
 motor2.run(RELEASE); /* Inicia com os motores parados */
 motor3.run(RELEASE);
}
void loop() {
 motor2.setSpeed(180); /* Defi ne a potÃªncia para os motores
(0-255) */
 motor3.setSpeed(180);
 /* Chama a funÃ§Ã£o frente por 1000 milissegundos */
 frente(1000);
 /* pausa de meio segundo */
 delay(500);
 /* Chama a funÃ§Ã£o rÃ© por 1000 milissegundos */
 re(1000);
 /* pausa de meio segundo */
 delay(500);
 
 /* Chama a funÃ§Ã£o girar em torno do centro no sentido antihorÃ¡rio por 1000 milissegundos */
giro_centro_antihorario(1000);
/* pausa de meio segundo */
delay(500);
/* Chama a funÃ§Ã£o girar em torno do centro no sentido horÃ¡rio
por 1000 milissegundos */
giro_centro_horario(1000);
/* pausa de meio segundo */
delay(500);
/* Chama a funÃ§Ã£o girar em torno da roda no sentido antihorÃ¡rio por 1000 milissegundos */
giro_roda_antihorario(1000);
/* pausa de meio segundo */
delay(500);
/* Chama a funÃ§Ã£o girar em torno da roda no sentido horÃ¡rio por
1000 milissegundos */
giro_roda_horario(1000);
/* pausa de cinco segundos */
delay(5000);
}
/* FunÃ§Ã£o que move para frente pelo tempo definido */
void frente(int tempo)
{
motor2.run(FORWARD);
motor3.run(FORWARD);
delay(tempo);
motor2.run(RELEASE);
motor3.run(RELEASE);
}
/* FunÃ§Ã£o que move para trÃ¡s pelo tempo definido */
void re(int tempo)
{
motor2.run(BACKWARD);
motor3.run(BACKWARD);
delay(tempo);
motor2.run(RELEASE);
motor3.run(RELEASE);
}
/* FunÃ§Ã£o que gira em torno do centro no sentido anti-horÃ¡rio
pelo tempo definido */
void giro_centro_antihorario(int tempo)
{
motor2.run(FORWARD);
motor3.run(BACKWARD);
delay(tempo);

motor2.run(RELEASE);
motor3.run(RELEASE);
}
/* FunÃ§Ã£o que gira em torno do centro no sentido horÃ¡rio pelo
tempo definido */
void giro_centro_horario(int tempo)
{
motor2.run(BACKWARD);
motor3.run(FORWARD);
delay(tempo);
motor2.run(RELEASE);
motor3.run(RELEASE);
}
/* FunÃ§Ã£o que gira em torno da roda no sentido anti-horÃ¡rio
pelo tempo definido */
void giro_roda_antihorario(int tempo)
{
motor2.run(FORWARD);
motor3.run(RELEASE);
delay(tempo);
motor2.run(RELEASE);
motor3.run(RELEASE);
}
/* FunÃ§Ã£o que gira em torno da roda no sentido horÃ¡rio pelo
tempo definido */
void giro_roda_horario(int tempo)
{
motor2.run(RELEASE);
motor3.run(FORWARD);
delay(tempo);
motor2.run(RELEASE);
motor3.run(RELEASE); 

}

