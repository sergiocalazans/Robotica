#include "arduino_secrets.h"

#include "DHT.h"
#include <RF24.h>

// DefiniÃ§Ãµes para o sensor DHT11
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// DefiniÃ§Ãµes para o mÃ³dulo nRF24L01
#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);

// EndereÃ§os de comunicaÃ§Ã£o
const byte address[6] = "00001";

// Pinos para os LEDs
#define LED_VERMELHO 4
#define LED_AMARELO 5
#define LED_VERDE 6

// Pino do sensor de umidade do solo
#define PINO_ANALOG A0

// Pino do relÃ©
#define PINO_RELE 8

// VariÃ¡vel que armazena a leitura analÃ³gica do sensor
int ValAnalogIn;

void setup() {
  // InicializaÃ§Ã£o da comunicaÃ§Ã£o serial
  Serial.begin(9600);

  // InicializaÃ§Ã£o do sensor DHT11
  dht.begin();

  // InicializaÃ§Ã£o dos pinos dos LEDs como saÃ­da
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // InicializaÃ§Ã£o do pino do relÃ© como saÃ­da
  pinMode(PINO_RELE, OUTPUT);

  // InicializaÃ§Ã£o do mÃ³dulo nRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  // Leitura da umidade do solo
  ValAnalogIn = analogRead(PINO_ANALOG);
  int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);

  // Controle dos LEDs conforme a umidade do solo
  if (Porcento <= 45) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
  } else if (Porcento <= 70) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  // Controle da irrigaÃ§Ã£o
  if (Porcento <= 45) {
    Serial.println("Irrigando a planta ...");
    digitalWrite(PINO_RELE, HIGH);
  } else {
    Serial.println("Planta irrigada ...");
    digitalWrite(PINO_RELE, LOW);
  }

  // Leitura da temperatura e umidade do ar
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // PreparaÃ§Ã£o dos dados para envio
  char data[32];
  snprintf(data, sizeof(data), "T:%.1f H:%.1f U:%d", t, h, Porcento);

  // Envio dos dados pelo mÃ³dulo nRF24L01
  radio.write(&data, sizeof(data));

  // ImpressÃ£o dos valores no monitor serial
  Serial.print("Umidade do solo: ");
  Serial.print(Porcento);
  Serial.println("%");
  Serial.print("Umidade do ar: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperatura do ar: ");
  Serial.print(t);
  Serial.println("Â°C");

  // Atraso de 1 segundo para a prÃ³xima leitura
  delay(1000);
}
