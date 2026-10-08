#include "arduino_secrets.h"

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal.h>

// DefiniÃ§Ãµes para o sensor DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ConfiguraÃ§Ãµes de rede WiFi
#ifndef SECRET_SSID
#define SECRET_SSID "NOME_DA_REDE"
#endif

#ifndef SECRET_PASS
#define SECRET_PASS "SENHA_DA_REDE"
#endif

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
ESP8266WebServer servidor(80);

// DefiniÃ§Ãµes para o display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pinos para os LEDs
#define LED_VERMELHO 7
#define LED_AMARELO 6
#define LED_VERDE 5

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

  // InicializaÃ§Ã£o do display LCD
  lcd.begin(16, 2);

  // ConfiguraÃ§Ã£o do ponto de acesso WiFi
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("Rede criada: ");
  Serial.println(ssid);

  // ConfiguraÃ§Ã£o do servidor web
  servidor.on("/", Pagina_Requisitada);
  servidor.onNotFound(Pagina_Inexistente);
  servidor.begin();
  Serial.println("Servidor iniciado");
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

  // AtualizaÃ§Ã£o do display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(h);
  lcd.print(" %");

  // Envio de dados pelo servidor web
  servidor.handleClient();

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

void Pagina_Requisitada() {
  servidor.send(200, "text/html", Monta_HTML());
}

void Pagina_Inexistente() {
  servidor.send(404, "text/html",
   "<H1><!DOCTYPE html><html>"
   "PÃ¡gina nÃ£o encontrada"
   "</H1></html>");
}

String Monta_HTML() {
  // Ler dados do sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Monitoramento de Plantas</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px; background: #009541;} h1 {color: #444444; margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px; color: #444444; margin-bottom: 10px;}\n";
  ptr += ".plant-status {font-size: 20px; margin-top: 20px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>&#127808; Monitoramento de Plantas &#127808;</h1>\n";
  ptr += "<h2>Temperatura: " + String(temp) + " &deg;C</h2>\n";
  ptr += "<h2>Umidade: " + String(hum) + " %</h2>\n";
  ptr += "<div class=\"plant-status\">\n";
  
  // Comparar com as condiÃ§Ãµes ideais das plantas
  struct Planta {
    const char* nome;
    float tempMin;
    float tempMax;
    float humMin;
    float humMax;
  };

  Planta plantas[] = {
    {"Espada-de-SÃ£o-Jorge", 18, 30, 20, 50},
    {"Samambaia", 15, 24, 60, 90},
    {"Jiboia", 18, 30, 40, 60},
    {"LÃ­rio-da-paz", 18, 27, 40, 80},
    {"Suculenta", 18, 25, 10, 30},
  };

  for (int i = 0; i < 5; i++) {
    if (temp >= plantas[i].tempMin && temp <= plantas[i].tempMax &&
        hum >= plantas[i].humMin && hum <= plantas[i].humMax) {
      ptr += "<p>" + String(plantas[i].nome) + " estÃ¡ em condiÃ§Ã£o ideal.</p>\n";
    } else {
      ptr += "<p>" + String(plantas[i].nome) + " NÃO estÃ¡ em condiÃ§Ã£o ideal.</p>\n";
    }
  }
  
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

