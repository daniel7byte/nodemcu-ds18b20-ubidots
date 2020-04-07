// This example sends data to multiple variables to
// Ubidots through HTTP protocol.
// https://github.com/ubidots/ubidots-esp8266 <-- Libreria Usada
// https://arduino.esp8266.com/stable/package_esp8266com_index.json <-- Tarjeta

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-ZVJ1tw9QLOB0heYmjpPYMC6tmdSKdT";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Leydig";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "94232607.";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN);

int i = -5;
int j = 0;

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {

  int m1 = 1;
  
  i = i + random(-2, 5);
  j = j + 1;

  if(j%3==0){
    if(m1==0){
      m1 = 1;
    }else{
      m1 = 0;
    }
  }
  
  // Publish values to 2 different data sources
  //ubidots.ubidotsPublish("nodemcu-1");
  ubidots.add("ds18b20-1", i);
  ubidots.add("maquina-1", m1);
  
  bool bufferSent = false;
  bufferSent = ubidots.send("nodemcu-1");  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Valores enviados al servidor");
  }

  delay(1000);
}
