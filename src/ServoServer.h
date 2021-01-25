/*
 * ServoServer.h
 *
 *  Created on: Mar 1, 2019
 *      Author: jmmckinney
 */

#ifndef SRC_SERVOSERVER_H_
#define SRC_SERVOSERVER_H_
#include <SimplePacketComs.h>
#include <ESP32Servo.h>
#define MAX_IO_SERVO 4
#define MAX_PCA9685_SERVO 16
#define MAX_POSSIBLE_SERVOS (MAX_IO_SERVO+MAX_PCA9685_SERVO)
#include <stdint.h>
#include <PCA9685.h>
#include "pinmap_smallkat.h"

class ServoServer : public PacketEventAbstract {
private :
	Servo listOfServo[MAX_IO_SERVO];
	PCA9685 pca9685;
	int maps [MAX_IO_SERVO];
	int cache[MAX_POSSIBLE_SERVOS];
	int flush=false;
	bool firstRun=true;
	bool new_data = false;

public:
	ServoServer();
	virtual ~ServoServer();
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
	void loopServos();
};

#endif /* SRC_SERVOSERVER_H_ */
