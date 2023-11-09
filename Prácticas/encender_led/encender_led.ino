const int LED = 13;
const int BUTTON = 2;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int val = digitalRead(BUTTON); // lee el estado del Boton
  if(val == HIGH){
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }
}
