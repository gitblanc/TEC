const int LED = 5;
const int BUTTON_MOTOR = 2;
const int BUTTON_BELT = 4;
const int BUZZER = 3;

void setup() {
  pinMode(BUTTON_MOTOR, INPUT_PULLUP);
  pinMode(BUTTON_BELT, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  int motor = digitalRead(BUTTON_MOTOR);
  int belt = digitalRead(BUTTON_BELT);
  //si el motor está encendido y el cinturón no está puesto, se enciende el led
  if(motor == HIGH && belt == LOW){
    digitalWrite(LED, HIGH);
    tone(BUZZER, 600);
  }else{
    digitalWrite(LED, LOW);
    noTone(BUZZER);
  }
}
