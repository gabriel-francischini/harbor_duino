void setup() {
  // Abre a serial com a velocidade de 9600
  Serial.begin(9600);
  while (!Serial){;} // Código necessário para alguns arduinos
}

void loop() {
  Serial.write(15);
  delay(500);
}
