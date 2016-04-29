#include "Arduino.h"
#include "transmissor.h"


byte t__buffer[80];
byte *t_p_buffer;
byte t__indice;

// Abre a porta serial
void iniciarTransmissao(){
  // Abre a serial com a velocidade de 9600
  Serial.begin(9600);
  // Código necessário para alguns arduinos
  while (!Serial){;} 

  // Inicia o buffer
  t_p_buffer = &t__buffer[0];

}


void processarTransmissao(){
  /*if(Serial.available() > 0){
    Serial.write(Serial.read());
    delay(1000);
  }*/
}

void enviar(int informacao){
  Serial.write(informacao);
  delay(200);
}

