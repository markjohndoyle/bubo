/*
 * TelemetryProducer.cpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 *
 */
#include "bubo/telemetry/RotorTelemetryProducer.hpp"
#include "channels/TelemetryOutputChannel.hpp"
#include "bubo/rotor/Rotor.hpp"
#include "Ethernet/util.h"
#include <pnew.cpp>  // placement new implementation

namespace bubo {
namespace telemetry {

using namespace rotor;
using namespace std;

const uint8_t RotorTelemetryProducer::LAYOUT_ID_POSITION = 1;

RotorTelemetryProducer::RotorTelemetryProducer(TelemetryOutputChannel* tmOutputChannel, Rotor* targetRotor)
	: rotor(targetRotor) {
	outputChannels.push_back(tmOutputChannel);
}

RotorTelemetryProducer::RotorTelemetryProducer(vector<TelemetryOutputChannel*> tmOutputChannels, Rotor* targetRotor)
	: rotor(targetRotor) {
	outputChannels = tmOutputChannels;
}

TelemetryPayload* RotorTelemetryProducer::produceTelemetry(TM_TYPE type) const {
	long azimuth = -9999;
	long elevation = -9999;
	switch (type) {
		case POSITION:
			azimuth = rotor->getCurrentAzimuth();
			elevation = rotor->getCurrentElevation();
			break;
	}

	unsigned long int payloadSize = sizeof(long) * 2;
	byte* const bytes = (byte*) ((malloc(payloadSize)));
	if (bytes != NULL) {
		bytes[1] = azimuth;
		bytes[2] = azimuth << 8;
		bytes[3] = azimuth << 16;
		bytes[4] = azimuth << 24;
		bytes[5] = elevation;
		bytes[6] = elevation << 8;
		bytes[7] = elevation << 16;
		bytes[8] = elevation << 24;

//		Serial.println("----------");
//		Serial.println(azimuth);
//		Serial.println(elevation);
//		Serial.println(bytes[0], BIN);
//		Serial.println(bytes[1], BIN);
//		Serial.println(bytes[2], BIN);
//		Serial.println(bytes[3], BIN);
//		Serial.println(bytes[4], BIN);
//		Serial.println(bytes[5], BIN);
//		Serial.println(bytes[6], BIN);
//		Serial.println(bytes[7], BIN);
//		Serial.println("");
	}
	else {
		Serial.println("Failed to allocate bytes for TM");
	}

	return new TelemetryPayload(bytes, 9);
}

void RotorTelemetryProducer::sendTelemetry(TM_TYPE type) const {
	TelemetryPayload* payload = produceTelemetry(type);
	for(uint16_t i = 0; i < outputChannels.size(); i++) {
		outputChannels[i]->output(payload, type);
	}

	delete payload;
}

} /* namespace telemetry */
} /* namespace bubo */
