#include <WiFi.h>
#include <WebServer.h>

// Parametros de la WiFi
const char* ssid = "ESP32-4";             
const char* password = "TEC12345678";   

// IP del servidor HTTP
IPAddress local_ip(192,168,20,1);
IPAddress gateway(192,168,20,1);
IPAddress subnet(255,255,255,0);

// declaraciones
WebServer server(80);
uint8_t LEDpin = 5;
uint8_t LEDpin2 = 4;
bool LEDstatus = LOW;
bool LEDstatus2 = LOW;   


// ---------------- SETUP  -----------------
void setup() {
  
  // Para logging
  Serial.begin(115200);
  // configuración pin LED como salida
  pinMode(LEDpin, OUTPUT);
  pinMode(LEDpin2, OUTPUT);

  //configuración WiFi modo AP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  // Funciones de callback según ruta de solicitud recibida
  server.on("/", handle_OnConnect);
  server.on("/H", handle_ledon);
  server.on("/L", handle_ledoff);
  server.on("/H1", handle_ledoff2);
  server.on("/L1", handle_ledon2);
  server.onNotFound(handle_NotFound);

  // Arranque del servidor
  server.begin();
  Serial.println("HTTP server started...");
}
// ---------------- FIN SETUP  -----------------



// ---------------- LOOP -----------------
void loop() {

  // Pooling esperando solicitudes del cliente
  server.handleClient();
  // actualización del estado del LED
  digitalWrite(LEDpin, !LEDstatus);    
  delay(2); // permite CPU cambiar a otras tareas
  digitalWrite(LEDpin2, !LEDstatus2);//para el led 2
  delay(2);
}
// ---------------- FIN LOOP  -----------------



// --------- Funciones de Callback -------------

void handle_OnConnect() {
  LEDstatus = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML()); 
}
void handle_ledon() {
  LEDstatus = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML()); 
}
void handle_ledoff() {
  LEDstatus = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML()); 
}

void handle_ledon2() {
  LEDstatus2 = HIGH;
  Serial.println("GPIO4 Status: ON");
  server.send(200, "text/html", SendHTML()); 
}
void handle_ledoff2() {
  LEDstatus2 = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML()); 
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
//  -------------------------------------------


// Construcción de la página Web   
String SendHTML(){
    String 
       ptr  ="<title>TEC LED Control</title>\n";
       ptr +="<h1>TEC ESP32 HTTP Server</h1>\n";
       ptr +=  "Clic <a href=\"/H\">aqui</a> para ENCEDER el LED del pin 5.<br><br>"; 
                          // \" para incluir  comillas en el texto
       ptr +=  "Clic <a href=\"/L\">aqui</a> para APAGAR el LED del pin 5.<br><br>";
       ptr +=  "Clic <a href=\"/H1\">aqui</a> para ENCENDER el LED del pin 4.<br><br>";
       ptr +=  "Clic <a href=\"/L1\">aqui</a> para APAGAR el LED del pin 4.<br><br>";

       return ptr;
}
