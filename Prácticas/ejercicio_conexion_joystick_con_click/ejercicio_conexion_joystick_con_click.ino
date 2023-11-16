#define joyX A0
#define joyY A1
const int switchPin = 2;
 
void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}
 
void loop() {
  // read the switch:
  int switchState = digitalRead(switchPin);
  
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
 
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\t");
  if(switchState == LOW){
    Serial.println("State of switch: pulsado");
  }else{
    Serial.println("State of switch: no pulsado");
  }
}
