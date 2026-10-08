#include "arduino_secrets.h"

int modo = 0;
int leitura = 0;
int buzzer = 1;
#define PIN_SENSOR 2
#define PIN_LED_VERDE_CAR 3
#define PIN_LED_AMARELO_CAR 4
#define PIN_LED_VERMELHO_CAR 5
#define PIN_LED_VERDE_PED 6
#define PIN_LED_VERMELHO_PED 7


void setup()
{
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
  for (int i = 3; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), sensorAcionado, FALLING);
}
void loop() {
  
  switch (modo) {
    case 0:
      modocarros();
      break;
    case 1:
      travessia();
      break;
  }
}

void sensorAcionado() {
  modo = 1;
  leitura =  analogRead(PIN_SENSOR); 
  Serial.print("leitura =  ");
  Serial.println(leitura);   
  // "o sinal jÃ¡ vai abrir" em cÃ³digo Morse
  String morseCode = "--- / ... .. -. .- .-.. / .--- / ...- .- .. / .- -... .-. .. .-.";
  for (int i = 0; i < morseCode.length(); i++)
    {
    if (morseCode.charAt(i) == '.')
    {
      tone(buzzer, 1000, 200); 
    }
    else if (morseCode.charAt(i) == '-')
    {
      tone(buzzer, 1000, 600); 
    }
    else if (morseCode.charAt(i) == ' ')
    {
      delay(600);
    }
    else if (morseCode.charAt(i) == '/')
    {
      delay(1200); 
    }
    delay(200); 
    noTone(buzzer); 
  }
  delay(1000);
}
  
void travessia() {
  delay(1000);
  digitalWrite(PIN_LED_VERDE_CAR, LOW);
  digitalWrite(PIN_LED_AMARELO_CAR, HIGH);
  delay(3000);
  digitalWrite(PIN_LED_VERDE_PED, HIGH);
  digitalWrite(PIN_LED_VERMELHO_PED, LOW);
  digitalWrite(PIN_LED_AMARELO_CAR, LOW);
  digitalWrite(PIN_LED_VERMELHO_CAR, HIGH);
  delay(5000);
  digitalWrite(PIN_LED_VERDE_PED, LOW);
  for (int i = 0; i <= 5; i++)
  {
    digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
    delay(300);
    digitalWrite(PIN_LED_VERMELHO_PED, LOW);
    delay(300);
  }
  modo = 0; 
}
void modocarros() {
  digitalWrite(PIN_LED_VERDE_PED, LOW);
  digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
  digitalWrite(PIN_LED_VERDE_CAR, HIGH);
  digitalWrite(PIN_LED_AMARELO_CAR, LOW);
  digitalWrite(PIN_LED_VERMELHO_CAR, LOW);
}