/*
 * ServoServer.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: jmmckinney
 */

#include "ServoServer.h"

ServoServer::ServoServer() :
		PacketEventAbstract(1962) {
	maps[0] = 15;
	maps[1] = 2;
	maps[2] = 4;
	maps[3] = 16;
	firstRun = true;
}

ServoServer::~ServoServer() {
	// TODO Auto-generated destructor stub
}
void ServoServer::loopServos() {
	if (flush) {
		if (firstRun) {
			pca9685.setupSingleDevice(Wire, 0x40);
			pca9685.setupOutputEnablePin(PWM_ENABLE_PIN);
			pca9685.enableOutputs(PWM_ENABLE_PIN);
			pca9685.setToServoFrequency();
		}
		if(new_data)
		{
			for (int i = 0; i < MAX_POSSIBLE_SERVOS; i++) {
				if (i >= MAX_PCA9685_SERVO) {
					int srvIndex = i - MAX_PCA9685_SERVO;
					if (firstRun) {
						listOfServo[srvIndex].setPeriodHertz(330);
						listOfServo[srvIndex].attach(maps[srvIndex], 1000, 2000);
					}

					listOfServo[srvIndex].write(cache[i]);
				} else {
					pca9685.setChannelServoPulseDuration(i,
							map(cache[i], 0, 180, 1000, 2000));
				}
			}
			new_data = false;
		}
		if (firstRun)
			firstRun = false;
	}

}

//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void ServoServer::event(float *buffer) {
	uint8_t *bBuffer = (uint8_t*) buffer;

	for (int i = 0; i < MAX_POSSIBLE_SERVOS; i++) {
		cache[i] = bBuffer[i];
	}
	flush = true;
	new_data = true;

}
