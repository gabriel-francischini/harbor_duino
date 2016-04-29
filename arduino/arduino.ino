#include "transmissor.h"

void setup() {

  iniciarTransmissao();
}
int i;
void loop() {
  for(; i < 800; i++)
  enviar(i);
  delay(10000);
  i = 0;
}
