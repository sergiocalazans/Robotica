#include "arduino_secrets.h"

/************************************************************/
/* Aula 12 - Sensor de umidade do solo                                */
/* ProgramaÃ§Ã£o do projeto sensor de umidade do solo.        */
/* Ao transferir o cÃ³digo abaixo para seu Arduino, o sensor */
/* de umidade do solo irÃ¡ monitorar a intensidade de umidade*/
/* da superfÃ­cie em que sua sonda estÃ¡ espetada (o solo).   */
/* De acordo com os dados obtidos pelo sensor, serÃ¡ possÃ­vel*/
/* identificar atravÃ©s de LEDs, baixa umidade (LED Vermelho)*/
/* ou umidade adequada (LED Verde) e tambÃ©m atravÃ©s do      */
/* monitor serial, por meio de mensagem informando a        */
/* condiÃ§Ã£o de umidade em tempo real.                       */
/************************************************************/
/* DefiniÃ§Ãµes de pinos para o sensor de umidade e LEDs.     */
#define pino_Sensor A0
#define pino_LED_Verde 3
#define pino_LED_Vermelho 4

/* Porcentagem de umidade em que o sistema delimitarÃ¡ a     */
/* condiÃ§Ã£o da umidade (baixa ou adequada).                 */
int Valor_Critico = 45;
/* VariÃ¡vel para armazenar o valor analÃ³gico do sensor.     */
int ValAnalogIn;
void setup() {
  /* Inicia a comunicaÃ§Ã£o Serial com velocidade de 9600     */
  /* bauds.                                                 */
  Serial.begin(9600);
  /* Configura os pinos dos LEDs como saÃ­da.                */
  pinMode(pino_LED_Verde, OUTPUT);
  pinMode(pino_LED_Vermelho, OUTPUT);
}
void loop() {
  /* Realiza a leitura do sensor e armazena o valor na      */
  /* variÃ¡vel ValAnalogIn.                                  */
  ValAnalogIn = analogRead(pino_Sensor);
  /* Converte o valor analÃ³gico para porcentagem.           */
  int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);
  /* Imprime o valor em porcentagem no Monitor Serial.      */
  Serial.print(Porcento);
  /* Imprime o sÃ­mbolo junto ao valor da porcentagem.       */
  Serial.println("%");
  /* Se a porcentagem for menor ou igual ao valor definido. */
  if (Porcento <= Valor_Critico) {
    /* Imprime a frase no Monitor Merial.                   */
    Serial.println("Umidade baixa!");
    /* Acende o LED Vermelho.                               */
    digitalWrite(pino_LED_Vermelho, HIGH);
    /* Apaga o LED Verde.                                   */
    digitalWrite(pino_LED_Verde, LOW);
  }
  else {
    /* Imprime a frase no Monitor Serial.                   */
    Serial.println("Umidade Adequada...");
    /* Acende o LED Verde.                                  */
    digitalWrite(pino_LED_Verde, HIGH);
    /* Apaga o LED Vermelho.                                */
    digitalWrite(pino_LED_Vermelho, LOW);
  }
  /* Aguarda 1 segundo para reiniciar a nova leitura.       */
  delay (1000);
}
