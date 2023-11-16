#include <Servo.h>

// Define los pines para el joystick
#define joyX A0
#define joyY A1

// Define los pines para los servomotores
#define servoXPin 9
#define servoYPin 10

Servo servoX;
Servo servoY;

void setup() {
  // Inicializa los servomotores
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  // Inicializa el puerto serial
  Serial.begin(9600);
}

void loop() {
  // Lee los valores del joystick
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);

  // Mapea los valores del joystick al rango de movimiento de los servomotores (0-180)
  int xAngle = map(xValue, 0, 1023, 0, 180);
  int yAngle = map(yValue, 0, 1023, 0, 180);

  // Mueve los servomotores a las posiciones calculadas
  servoX.write(xAngle);
  servoY.write(yAngle);

  // Imprime los valores para depuración
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print("\tY: ");
  Serial.print(yValue);
  Serial.print("\tServoX: ");
  Serial.print(xAngle);
  Serial.print("\tServoY: ");
  Serial.println(yAngle);
}
