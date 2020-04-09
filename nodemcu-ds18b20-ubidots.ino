// This example sends data to multiple variables to
// Ubidots through HTTP protocol.
// https://github.com/ubidots/ubidots-esp8266 <-- Libreria Usada
// https://arduino.esp8266.com/stable/package_esp8266com_index.json <-- Tarjeta

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"
#include <OneWire.h>
#include <DallasTemperature.h>

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-ZVJ1tw9QLOB0heYmjpPYMC6tmdSKdT";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Leydig";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "94232607.";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN);

// Data wire is plugged into port D2 on the ESP8266
#define ONE_WIRE_BUS D2

//Machines
int MAQUINA_1 = 5; // D1(GPIO5)
int MAQUINA_1_STATE = 0;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

float tempSensor1, tempSensor2, tempSensor3;

uint8_t sensor1[8] = { 0x28, 0x8E, 0x41, 0x94, 0x97, 0x0C, 0x03, 0xD1  };
uint8_t sensor2[8] = { 0x28, 0x7D, 0x1E, 0x94, 0x97, 0x0C, 0x03, 0x00  };

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  sensors.begin();
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages

  pinMode(MAQUINA_1, INPUT);
}

void loop() {

  sensors.requestTemperatures();
  tempSensor1 = sensors.getTempC(sensor1); // Gets the values of the temperature
  tempSensor2 = sensors.getTempC(sensor2); // Gets the values of the temperature
  
  // Publish values to 2 different data sources
  //ubidots.ubidotsPublish("nodemcu-1");
  ubidots.add("ds18b20-1", tempSensor1);
  ubidots.add("ds18b20-2", tempSensor2);
  
  //Maquinaria
  MAQUINA_1_STATE = digitalRead(MAQUINA_1); // put your main code here, to run repeatedly:
  ubidots.add("maquina-1", MAQUINA_1_STATE);

  // Envia la informacion
  bool bufferSent = false;
  bufferSent = ubidots.send("nodemcu-1");  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Valores enviados al servidor");
  }

  delay(1000);
}
