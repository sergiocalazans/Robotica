#include "arduino_secrets.h"

#include <L298NX2.h>

// DefiniÃ§Ã£o dos pinos do motor
#define ENA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5

// CriaÃ§Ã£o do objeto de controle dos motores
L298NX2 motores(ENA, IN1, IN2, ENB, IN3, IN4);

// FunÃ§Ã£o para definir a velocidade do carrinho
void setSpeed(int speed) {
  motores.setSpeed(speed);
}

// FunÃ§Ã£o para mover o carrinho para frente constantemente
void frente_constante() {
  motores.forward();
}

void setup() {
  // InicializaÃ§Ã£o da comunicaÃ§Ã£o serial
  Serial.begin(9600);

  // InicializaÃ§Ã£o dos motores
  motores.stop();
}

void loop() {
  // DefiniÃ§Ã£o de uma velocidade alta
  int speed = 255; // MÃ¡xima velocidade 255
  
  // DefiniÃ§Ã£o da velocidade do carrinho
  setSpeed(speed);

  // Movimento do carrinho para frente constante
  while (true) {
    frente_constante();
  }
}
