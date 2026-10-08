#include "arduino_secrets.h"

/* Programa: CÃ³digo Morse */
/* Definindo os pinos do Buzzer, botÃ£o e LED */
int buzzer = 2;
int botao = 3;
int LED = 4;

int LDR = A0; 
int leitura = 0;

void setup()
{
  /* Define os pinos do LED e Buzzer como saÃ­da */
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  /* Define o pino do botÃ£o como entrada e ativa o resistor
    interno */
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}
void loop() {
  leitura =  analogRead(LDR); 
  
  Serial.println(leitura);   
  if (leitura > 800)
  {
    digitalWrite(LED, HIGH);
    // "OLA, TUDO BEM?" em cÃ³digo Morse
    String morseCode = ".-..-. --- .-.. .- --..-- / - ..- -.. --- / -... . -- ..--.. .-..-.";
    for (int i = 0; i < morseCode.length(); i++)
    
    {
      if (morseCode.charAt(i) == '.')
      {
        tone(buzzer, 1000, 200); // Ponto
      }
      else if (morseCode.charAt(i) == '-')
      {
        tone(buzzer, 1000, 600); // TraÃ§o
      }
      else if (morseCode.charAt(i) == ' ')
      {
        delay(600); // EspaÃ§o entre letras
      }
      else if (morseCode.charAt(i) == '/')
      {
        delay(1200); // EspaÃ§o entre palavras
      }
      delay(200); // Pausa entre pontos e traÃ§os
      noTone(buzzer); // Desliga o buzzer
    }
    delay(1000); // Pausa entre a mensagem e o fim do loop
  }
  /* SenÃ£o desligue o LED e pare o som */
  else
  {
    digitalWrite(LED, LOW);
    noTone(buzzer);
  }
}







