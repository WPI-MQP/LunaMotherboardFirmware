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
String * name = new String("midnight");
Adafruit_BNO055 bno;
GetIMU * sensor;
ServoServer * servos;
TwoWire Wire_2 = TwoWire(1);

void setup()
{
	manager.setup();
	sensor = new GetIMU();
  Wire.begin(32,27);
  Wire_2.begin(21,22); // SDA pin 16, SCL pin 17, 400kHz frequency
	Serial.println("Loading with name: "+name[0]);
	servos=new ServoServer();

	//Initialise the sensor
  bno = Adafruit_BNO055(55, 0x28, &Wire_2);

	if (bno.begin()) {
		delay(1000);
		bno.setExtCrystalUse(true);
		sensor->startSensor(&bno);
	}else{
		Serial.print(
				"Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
	}

	coms.attach(new NameCheckerServer(name));
	coms.attach(sensor);
	coms.attach(servos);
}

// The loop function is called in an endless loop
void loop()
{
	manager.loop();
	coms.server();
	servos->loopServos();
}
