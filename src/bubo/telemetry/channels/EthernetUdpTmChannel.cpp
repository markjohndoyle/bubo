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

EthernetUdpTmChannel::EthernetUdpTmChannel() :
		udpServerPort(5478) {
	config.broadcastAddress = IPAddress(192, 168, 0, 255);
	config.broadcastPort = 4023;
}

EthernetUdpTmChannel::~EthernetUdpTmChannel() {
	udp.stop();
}

int EthernetUdpTmChannel::beginUdpPacket(uint16_t port) {
	return udp.beginPacket(config.broadcastAddress, port);

}

}

void EthernetUdpTmChannel::sendPacket(const TelemetryPayload* const tmPayload) {
	udp.write(tmPayload->getPayload(), tmPayload->getSize());
	udp.endPacket();
	udp.stop();
}

void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload, uint16_t port) {
	if (beginUdpPacket(port) != -1) {
		sendPacket(tmPayload);
	}
	else {
		Serial.println("[ERROR] - Could not create UDP packet with supplied remote ip and port");
	}
}

void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload) {
	if (beginUdpPacket(config.broadcastPort) != -1) {
		sendPacket(tmPayload);
	}
	else {
		Serial.println("[ERROR] - Could not create UDP packet with supplied remote ip and port");
	}
}

bool EthernetUdpTmChannel::saveSettings() {
	// TODO implement method
	return false;
}

bool EthernetUdpTmChannel::loadSettings() {
	// TODO implement method
	return false;
}

void EthernetUdpTmChannel::setBroadcastAddress(IPAddress newAddress) {
	config.broadcastAddress = newAddress;
}

void EthernetUdpTmChannel::setBroadcastPort(uint16_t newPort) {
	config.broadcastPort = newPort;
}

}/* namespace telemetry */
} /* namespace bubo */
