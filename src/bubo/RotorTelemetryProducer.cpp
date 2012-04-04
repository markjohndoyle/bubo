/*
 * TelemetryProducer.cpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 *
 */
#include "bubo/RotorTelemetryProducer.hpp"
#include "Ethernet/util.h"

using namespace bubo;

const uint8_t RotorTelemetryProducer::LAYOUT_ID_POSITION = 1;

RotorTelemetryProducer::RotorTelemetryProducer(RotorInterface* rotorInterface) : rotor(rotorInterface) {
}

TelemetryPayload RotorTelemetryProducer::produceTelemetry(TM_TYPE type) {
	long azimuth = -9999;
	long elevation = -9999;
	uint_fast8_t id = 0;
	switch(type) {
		case POSITION:
			azimuth = rotor->getCurrentAzimuth();
			elevation = rotor->getCurrentElevation();
			id = LAYOUT_ID_POSITION;
			break;
	}

	azimuth = htonl(azimuth);
	elevation = htonl(elevation);

	unsigned long int payloadSize = (sizeof(long) * 2) + sizeof(uint_fast8_t);
	byte* const bytes = (byte*) (malloc(payloadSize));
	if (bytes != NULL) {
		bytes[0] = id;
		bytes[1] = azimuth;
		bytes[2] = azimuth << 8;
		bytes[3] = azimuth << 16;
		bytes[4] = azimuth << 24;
		bytes[5] = elevation;
		bytes[6] = elevation << 8;
		bytes[7] = elevation << 16;
		bytes[8] = elevation << 24;
	}
	else {
		Serial.println("Failed to allocate bytes for TM");
	}

	return bubo::TelemetryPayload(bytes, 4, id);
}
