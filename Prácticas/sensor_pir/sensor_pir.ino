const int LEDPin= 13;
const int PIRPin= 4;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  pinMode(PIRPin, INPUT);
}

void loop()
{
  int value= digitalRead(PIRPin);
 
  if (value == HIGH)
  {
    digitalWrite(LEDPin, HIGH);
    delay(1000);
    Serial.println("Hay movimiento");
  }
  else
  {
    digitalWrite(LEDPin, LOW);
    delay(1000);
    Serial.println("No hay movimiento");
  }
}
