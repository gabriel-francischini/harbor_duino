/*! \file arduino.ino Arquivo principal responsável por ser lido pelo Arduino IDE */

#include "transmissor.h"

//! Primeira função do arduino a ser executada
void setup() {

  iniciarTransmissao();
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
}
int i;

//! Função principal do arduino
void loop() {
  /*for(; i < 800; i++)
  enviar(i);
  delay(10000);
  i = 0;*/
  digitalWrite(2,LOW);
  analogWrite(3,150);
  digitalWrite(4,HIGH);
  analogWrite(5,25);
  digitalWrite(6,LOW);
  processarTransmissao();
}
