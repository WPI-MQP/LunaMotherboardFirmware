#include "Arduino.h"
#include <ESP32Servo.h>
#include <SimplePacketComs.h>
#include <WiFi.h>
#include <PacketEvent.h>
#include <Esp32SimplePacketComs.h>
#include <server/UDPSimplePacket.h>
#include <Preferences.h>
#include <Esp32WifiManager.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>
#include "src/ServoServer.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <PCA9685.h>
#include "src/GetIMU.h"
#include <Wire.h>
// SImple packet coms implementation useing WiFi
UDPSimplePacket coms;

// WIfi stack managment state machine
WifiManager manager;
//The setup function is called once at startup of the sketch
String * name = new String("HAL2001");
Adafruit_BNO055 bno;
GetIMU * sensor;
ServoServer * servos;
int toggled = 0;
void setup()
{
  pinMode(HEARTBEAT_LED, OUTPUT);
	manager.setupAP();
	Serial.println("Loading with name: "+name[0]);
	servos=new ServoServer();


	coms.attach(new NameCheckerServer(name));

	coms.attach(servos);
  toggled = millis();

}

// The loop function is called in an endless loop
void loop()
{
	manager.loop();
	coms.server();
 if(millis()-toggled >500)
 { 
  digitalWrite(HEARTBEAT_LED, !digitalRead(HEARTBEAT_LED));
  toggled = millis();
  
 }
}
