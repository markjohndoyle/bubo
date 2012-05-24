/*
 * EthernetUdpTmChannel.cpp
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#include "EthernetUdpTmChannel.hpp"
#include "bubo/telemetry/TelemetryPayload.hpp"
#include "Ethernet/Ethernet.h"

namespace bubo {
namespace telemetry {

EthernetUdpTmChannel::EthernetUdpTmChannel() :
		udpServerPort(5478) {
	config.broadcastAddress = IPAddress(192, 168, 0, 255);
//	config.broadcastAddress = IPAddress(10, 48, 31, 255);
	config.broadcastPort = 4023;

}

EthernetUdpTmChannel::~EthernetUdpTmChannel() {
	udp.stop();
}

void EthernetUdpTmChannel::initTmChannel() {
	IPAddress localIpAddress = IPAddress(192, 168, 0, 20);
	Ethernet.begin(MAC, localIpAddress);
}

void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload, RotorTelemetryProducer::TM_TYPE type) {
	const uint16_t port = BASE_PORT + type;

	if (udp.begin(udpServerPort) == 0) {
		return;
	}

	if (udp.beginPacket(config.broadcastAddress, port) == 0 ) {
		return;
	}

	if (udp.write(tmPayload->getPayload(), tmPayload->getSize()) != tmPayload->getSize()) {
		return;
	}
	udp.endPacket();
	udp.stop();
}

void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload) {
	output(tmPayload, RotorTelemetryProducer::POSITION);
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
