#include "arduino_secrets.h"

/********************************************************/
/* Aula 38 - RobÃ´ SumÃ´                                  */
/* ProgramaÃ§Ã£o: Abaixo um exemplo de cÃ³digo que         */
/* controlarÃ¡ o robÃ´ a disputa de sumÃ´. Ã utilizado dois*/
/* mÃ³dulos sensores de obstÃ¡culo IR para detectar a     */
/* borda da arena, um mÃ³dulo sensor ultrassÃ´nico para   */
/* detectar o adversÃ¡rio e a ponte H para fazer o       */
/* controle dos motores DC.                             */
/* Links para obtenÃ§Ã£o das bibliotecas                  */
/*                                                      */
/* http://librarymanager/All#minimalist#Ultrasonic      */
/* https://github.com/ErickSimoes/Ultrasonic            */
/* Biblioteca Ultrasonic by Erick SimÃµes                */
/*                                                      */
/* http://librarymanager/All#L298N#EASY                 */
/* https://github.com/AndreaLombardo/L298N              */
/* Biblioteca da ponte H by Andrea Lombardo.            */
/********************************************************/

/* Inclui as bibliotecas para controle da ponte H sensor*/
/* ultrassÃ´nico.                                        */
#include <L298NX2.h>
#include <Ultrasonic.h>

#define ENA 10  // ENA precisa estar em uma porta PWM
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5  // ENB precisa estar em uma porta PWM

/* Definimos os pinos do sensor ultrassÃ´nico.           */
#define Pino_Trig 12
#define Pino_Echo 11

/* Define os pinos para os sensores IR                  */
#define Pino_Sensor_Dianteiro 3
#define Pino_Sensor_Traseiro 2

/* Criamos um objeto de controle dos motores.           */
L298NX2 motores(ENA, IN1, IN2, ENB, IN3, IN4);
/* Criamos um objeto de controle para o ultrassÃ´nico.   */
Ultrasonic ultrasonic(Pino_Trig, Pino_Echo);
/* DeclaraÃ§Ã£o de variÃ¡veis:                             */
/* VariÃ¡vel "distancia" armazenarÃ¡ a distÃ¢ncia lida     */
/* pelo Sensor UltrassÃ´nico;                            */
/* VariÃ¡veis "IR_Dianteiro" e "IR_Traseiro" armazenarÃ£o */
/* a leitura dos Sensores Infravermelho;                */
/* VariÃ¡veis "Vel_Ataque" e "Vel_Padrao" definirÃ£o as   */
/* velocidades de movimento do robÃ´;                    */
/* VariÃ¡vel "tempo" define o tempo de delay nas funÃ§Ãµes.*/
int distancia, IR_Dianteiro, IR_Traseiro;
int Vel_Ataque = 255, Vel_Padrao = 80, distancia_ataque = 15;

void setup() {
  /* Configura os pinos dos sensores IR como entradas   */
  pinMode(Pino_Sensor_Dianteiro, INPUT);
  pinMode(Pino_Sensor_Traseiro, INPUT);
  delay(3000); /* Aguarda 3 segundos para iniciar       */
  /* Seta a velocidade dos motores.                     */
  motores.setSpeed(Vel_Padrao);
}

void loop() {
  /* Chama a funÃ§Ã£o criada para a leitura dos sensores. */
  ler_sensores();
  /* Se o sensor dianteiro detectar a linha, faÃ§a...    */
  if (IR_Dianteiro == 1) {
    Pare();
    Re();
    Pare();
    Manobre();
    Pare();
  }
  /* Se o sensor traseiro detectar a linha, faÃ§a...     */
  if (IR_Traseiro == 1) {
    Pare();
    motores.setSpeed(Vel_Ataque);
    Ataque();
    delay(500);
    motores.setSpeed(Vel_Padrao);
  }
  /* Se o sensor ultassÃ´nico detectar o adversÃ¡rio,    */
  /* faÃ§a...                                           */
  if (distancia <= distancia_ataque) {
    /*  Enquanto o sensor dianteiro nÃ£o chegar atÃ© a   */
    /* linha, faÃ§a...                                  */
    while (IR_Dianteiro == 0) {
      motores.setSpeed(Vel_Ataque);
      Ataque();
      /* Atualiza as informaÃ§Ãµes dos sensores.         */
      ler_sensores();
    }
    motores.setSpeed(Vel_Padrao);
  }
  /* Chama a funÃ§Ã£o que move o robÃ´ par frente.        */
  Frente();
}

/* FunÃ§Ãµes criadas para operaÃ§Ã£o do robÃ´ sumÃ´.         */

/* FunÃ§Ã£o fÃ¡ra as leituras dos sensores.               */
void ler_sensores() {
  distancia = ultrasonic.read();
  IR_Dianteiro = digitalRead(Pino_Sensor_Dianteiro);
  IR_Traseiro = digitalRead(Pino_Sensor_Traseiro);
}

/* FunÃ§Ã£o que move o robÃ´ para frente.                 */
void Frente() {
  motores.forward();
  delay(1);
}

/* FunÃ§Ã£o que move o robÃ´ para trÃ¡s.                   */
void Re() {
  motores.backward();
  delay(500);
}

/* FunÃ§Ã£o parar o robÃ´.                                */
void Pare() {
  motores.stop();
  delay(1);
}

/* FunÃ§Ã£o que faz o ataque do robÃ´.                    */
void Ataque() {
  motores.forward();
  delay(1);
}

/* FunÃ§Ã£o parar manobrar o robÃ´.                       */
void Manobre() {
  if (random(1, 3) == 1) {
    motores.forwardA();
    motores.backwardB();
  } else {
    motores.forwardB();
    motores.backwardA();
  }
  delay(250);
}
