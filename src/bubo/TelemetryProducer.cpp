/*
 * TelemetryProducer.cpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 *
 */
#include "bubo/TelemetryProducer.hpp"
#include "Ethernet/util.h"

using namespace bubo;

RotorTelemetryProducer::RotorTelemetryProducer(RotorInterface* rotorInterface) : rotor(rotorInterface) {
}

TelemetryPayload RotorTelemetryProducer::produceTelemetry(TM_TYPE type) {
	long value = -999;
	switch(type) {
		case AZIMUTH:
			value = rotor->getCurrentAzimuth();
			break;
		case ELEVATION:
			value = rotor->getCurrentElevation();
			break;
	}

	value = htonl(value);

	// Create 4 byte array.
	byte* const bytes = (byte*) malloc(sizeof(long));
	if (bytes != NULL) {
		bytes[0] = value;
		bytes[1] = value >> 8;
		bytes[2] = value >> 16;
		bytes[3] = value >> 24;
	}
	else {
		Serial.println("Failed to allocate 4 bytes for TM");
	}

	return bubo::TelemetryPayload(bytes, 4);
}

