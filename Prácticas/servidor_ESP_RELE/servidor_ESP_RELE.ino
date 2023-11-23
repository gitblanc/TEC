// Incluye la biblioteca de ESP32
#include <Arduino.h>

// Define el pin al que está conectado el relé
const int pinRelay = 4;

void setup() {
  // Inicializa el pin del relé como salida
  pinMode(pinRelay, OUTPUT);

  // Apaga el relé al inicio (puedes cambiar HIGH por LOW si el relé es activado con bajo nivel)
  digitalWrite(pinRelay, HIGH);
}

void loop() {
  // Activa el relé durante 2 segundos
  digitalWrite(pinRelay, LOW);
  delay(2000);

  // Desactiva el relé durante 2 segundos
  digitalWrite(pinRelay, HIGH);
  delay(2000);
}
