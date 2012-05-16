/*
 * EthernetUdpTmChannel.cpp
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#include "EthernetUdpTmChannel.hpp"
#include "bubo/telemetry/TelemetryPayload.hpp"

namespace bubo {
namespace telemetry {

EthernetUdpTmChannel::EthernetUdpTmChannel()
	: udpServerPort(5478) {
	config.broadcastAddress = IPAddress(192, 168, 0, 255);
	config.broadcastPort = 4023;
}

EthernetUdpTmChannel::~EthernetUdpTmChannel() {
	udp.stop();
}


void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload) {
	int check = udp.beginPacket(config.broadcastAddress, config.broadcastPort);
	if(check != 1) {
		Serial.println("[ERROR] - Could not create UDP packet with supplied remote ip and port");
		return;
	}
	udp.write(tmPayload->getPayload(), tmPayload->getSize());
	udp.endPacket();
	udp.stop();
}

bool EthernetUdpTmChannel::saveSettings() {
	// TODO implement method
}

bool EthernetUdpTmChannel::loadSettings() {
	// TODO implement method
}

}/* namespace telemetry */
} /* namespace bubo */
