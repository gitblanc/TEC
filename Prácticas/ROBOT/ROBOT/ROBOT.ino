#define AIN1_pin  2 // pines control motor derecho
#define AIN2_pin  3 //

#define BIN1_pin  4 // pines control motor izquierdo
#define BIN2_pin  5 //

#define PWMA_pin  9 // velocidad motor derecho   PWM
#define PWMB_pin  10 // velocidad motor izquierdo PWM

#define STBY_pin  13 // habilitación de motores (Standby)

#define Photo_Left_pin  A0 //   pin del Arduino conectado al sensor óptico Izquierdo
#define Photo_Right_pin A1 //   pin del Arduino conectado al sensor óptico Derecho

int Photo_Left = 0;
int Photo_Right = 0;

void setup() {
  Serial.begin(9600);
  // inicialización de los pines de control del motor
  pinMode(AIN1_pin, OUTPUT);
  pinMode(AIN2_pin, OUTPUT);
  pinMode(BIN1_pin, OUTPUT);
  pinMode(BIN2_pin, OUTPUT);

  // inicialización de pines sensores ópticos
  pinMode(Photo_Left_pin, INPUT);
  pinMode(Photo_Right_pin, INPUT);
  pinMode(STBY_pin, OUTPUT);

  digitalWrite(STBY_pin , 1);      // habilitación de motores
  delay(200);
  set_velocity(90);             // fija una velocidad 90

}

void sigueLinea() {
  Photo_Left = analogRead(Photo_Left_pin);
  Photo_Right = analogRead(Photo_Right_pin);
  //Serial.print("Left: ");
  //Serial.println(Photo_Left);
  //Serial.print("Right: ");
  //Serial.println(Photo_Right);
  int state = asignarState(Photo_Left, Photo_Right);//estado del robot
  //Serial.println("State: " + state);
  switch (state) {
    case 0:   //   avance
      goForward();
      delay(10);
      break;
    case 1:   //   giro a la izquierda
      right();
      delay(10);
      break;
    case 2:   //    giro a la derecha
      left();
      delay(10);
      break;
    case -1: //  se para
    default:
      stopMovement();
      break;
  }
}

int asignarState(int left, int right) {
  if (left < 150 && right < 150) {
    return 0;
  } else if (left >= 150 && right < 150) {
    return 1;
  } else if (left < 150 && right >= 150) {
    return 2;
  }
  return -1;
}


//-----------------------------
// Funcion de avance del motor
//-----------------------------
void goForward() {
  digitalWrite(AIN1_pin, HIGH); // motor derecho
  digitalWrite(AIN2_pin, LOW);
  digitalWrite(BIN1_pin, HIGH); // mmotor izquierdo
  digitalWrite(BIN2_pin, LOW);

} // ---------------------------

void stopMovement() {
  digitalWrite(AIN1_pin, LOW); // motor derecho
  digitalWrite(AIN2_pin, LOW);
  digitalWrite(BIN1_pin, LOW); // mmotor izquierdo
  digitalWrite(BIN2_pin, LOW);
}

//-----------------------------
// Funcion de atras del motor
//-----------------------------
void goBackwards() {
  digitalWrite(AIN1_pin, LOW); // motor derecho
  digitalWrite(AIN2_pin, HIGH);
  digitalWrite(BIN1_pin, LOW); // mmotor izquierdo
  digitalWrite(BIN2_pin, HIGH);
} // ---------------------------

//-----------------------------
// Funcion de girar izquierda del motor
//-----------------------------
void left() {
  digitalWrite(AIN1_pin, HIGH); // motor derecho
  digitalWrite(AIN2_pin, LOW);
  digitalWrite(BIN1_pin, LOW); // mmotor izquierdo
  digitalWrite(BIN2_pin, LOW);
} // ---------------------------

//-----------------------------
// Funcion de girar derecha del motor
//-----------------------------
void right() {
  digitalWrite(AIN1_pin, LOW); // motor derecho
  digitalWrite(AIN2_pin, LOW);
  digitalWrite(BIN1_pin, HIGH); // mmotor izquierdo
  digitalWrite(BIN2_pin, LOW);
} // ---------------------------



//----------------------------------------
// Función que fija la velocidad del robot
//-----------------------------------------
void set_velocity (byte velocity) {
  analogWrite(PWMA_pin, velocity);
  analogWrite(PWMB_pin, velocity);
}

void loop() {
  // test de movimentos del robot: avance, atras, giros
  // ---------------------------------------------------
  //goForward();
  //delay(2000);
  //goBackwards();
  //delay(2000);
  //right();
  //delay(1000);
  //left();
  //delay(1000);
  //digitalWrite(STBY_pin , 0);      // deshabilitación de motores

  sigueLinea();
//  Photo_Left = analogRead(Photo_Left_pin);
//  Photo_Right = analogRead(Photo_Right_pin);
//  Serial.print("Left: ");
//  Serial.println(Photo_Left);
//  Serial.print("Right: ");
//  Serial.println(Photo_Right);
//  delay(1000);
}
