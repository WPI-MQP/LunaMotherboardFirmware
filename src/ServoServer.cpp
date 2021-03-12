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


//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void ServoServer::event(float *buffer) {
	uint8_t *bBuffer = (uint8_t*) buffer;

	for (int i = 0; i < MAX_POSSIBLE_SERVOS; i++) {
		cache[i] = bBuffer[i];
	}
	flush = true;
	Serial.println("\n\n\nHAL\n\n");
}
