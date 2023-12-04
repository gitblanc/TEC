// =====================================
// PROGRAMA DEL MODULO RECEPTOR - ROBOT
// =====================================
// TRABAJO EN GRUPO
// TECNOLOGIA ELECTRONICA DE COMPUTADORES 
// UNIVERSIDAD DE OVIEDO
// (C) jC Anton 2022
//
// ATENCION !!!  
// Este programa debe cargarse en el uC del ROBOT. 
// El programa es una plantilla, debe completarse
//
// Pasos para ejecutarlo: 
// 
// 1. cargar el programa en el uC del robot.
// 3. Chequear que el interruptor "serial" 
//    del modulo transmisor esta en OFF.  
// 4. Resetear el robot 
// ==============================================

#include <SoftwareSerial.h>

#define AIN1_pin  2 // pines control motor derecho
#define AIN2_pin  3 //

#define BIN1_pin  4 // pines control motor izquierdo
#define BIN2_pin  5 //

#define PWMA_pin  9 // velocidad motor derecho   PWM
#define PWMB_pin  10 // velocidad motor izquierdo PWM

#define STBY_pin  13 // habilitación de motores (Standby)

#define Photo_Left_pin  A0 //   pin del Arduino conectado al sensor óptico Izquierdo
#define Photo_Right_pin A1 //   pin del Arduino conectado al sensor óptico Derecho
#define DEBUG

// ... declaraciones de los pines

// formato del frame 
struct __attribute__((packed)) frame_t {
byte Joystick_eje_X_data;
byte Joystick_eje_Y_data;
};


frame_t frame;

// Puerto serie por software sobre pin 12 (lectura) 
// pin RX-mySerial (12) is connected to Xbee pin DOUT  (2)
// pin TX-mySerial (11) is connected to Xbee pin DIN   (3)  no necesario  
SoftwareSerial mySerial(12, 11);                   //  




void setup() {
  //inicializa el puerto software para recibir datos del modulo Joystick
  mySerial.begin(9600);  
  //initializa UART serie para depuracion
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

  set_velocity(120);             // fija una velocidad 

}  // fin setup


//----------------
// Bucle principal
//----------------
void loop(){
  // comprueba que en el buffer de recepecion hay 2 bytes al menos
  if (mySerial.available() > 1) {                        
    // lectura de los bytes transmitidos
    frame.Joystick_eje_X_data  =  mySerial.read();       
    frame.Joystick_eje_Y_data  =  mySerial.read();

    byte state = asignarState(frame.Joystick_eje_X_data, frame.Joystick_eje_Y_data);//estado del robot
    switch(state){
      case 0:   //   avance
        goForward();
        set_velocity(255 - frame.Joystick_eje_X_data);
        break;
      case 1:   //   giro a la izquierda 
        right();
        set_velocity(frame.Joystick_eje_Y_data);
        break;
      case 2:   //    giro a la derecha
        left();
        set_velocity(255 - frame.Joystick_eje_Y_data);
        break;
      case 3: //  se para
        stopMovement();
        break;
      case 4: // hacia atrás
        goBackwards();
        set_velocity(frame.Joystick_eje_X_data);
        break;
    }
  }
          

  // para depurar por la consola del IDE Arduino (ASCII)      
  // cuando sea necesario
  #ifdef DEBUG 
    Serial.print("Axis X:");
    Serial.print(frame.Joystick_eje_X_data);
    Serial.print("\tAxis Y:");
    Serial.println(frame.Joystick_eje_Y_data);
  #endif

 


} // fin if

//-----------------------------
// Funcion de avance del motor
//-----------------------------
void goForward() {
  digitalWrite(AIN1_pin, HIGH); // motor derecho
  digitalWrite(AIN2_pin, LOW);   
  digitalWrite(BIN1_pin, HIGH); // mmotor izquierdo
  digitalWrite(BIN2_pin, LOW);      
} // ---------------------------

void stopMovement(){
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
  digitalWrite(BIN2_pin, HIGH);      
} // ---------------------------

//-----------------------------
// Funcion de girar derecha del motor
//-----------------------------
void right() {
  digitalWrite(AIN1_pin, LOW); // motor derecho
  digitalWrite(AIN2_pin, HIGH);   
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


byte asignarState(int x, int y){
  if ((x > 100 && x < 200) && (y > 100 && y < 200)) {
    return 3;
  } else if (x > 200 && (y > 100 && y < 200)) {
    return 4;
  } else if ((x > 100 && x < 200) && y > 200) {
    return 1;
  } else if ((x > 100 && x < 200) && y < 200) {
    return 2;
  } else if (x < 200 && (y > 100 && y < 200)) {
    return 0;
  }
  return 3;
}

