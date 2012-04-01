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

const uint8_t RotorTelemetryProducer::AZIMUTH_ID = 1;
const uint8_t RotorTelemetryProducer::ELEVATION_ID = 2;

RotorTelemetryProducer::RotorTelemetryProducer(RotorInterface* rotorInterface) : rotor(rotorInterface) {
}

TelemetryPayload RotorTelemetryProducer::produceTelemetry(TM_TYPE type) {
	long value = -9999;
	uint8_t id = 0;
	switch(type) {
		case AZIMUTH:
			value = rotor->getCurrentAzimuth();
			id = AZIMUTH_ID;
			break;
		case ELEVATION:
			value = rotor->getCurrentElevation();
			id = ELEVATION_ID;
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

	return bubo::TelemetryPayload(bytes, 4, id);
}

