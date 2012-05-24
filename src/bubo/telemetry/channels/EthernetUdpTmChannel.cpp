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
	Serial.println("About to call Ethernet.begin()");
	Ethernet.begin(MAC, localIpAddress);
	Serial.println("About to call udp.begin()");
	if (udp.begin(udpServerPort) == 0) {
		Serial.println("Error beginning UDP: No sockets available");
	} else {
		Serial.println("UDP came up successfully.");
	}

	for (int i=0; i<1; i++)
	{
		udp.beginPacket(config.broadcastAddress, config.broadcastPort);
		Serial.println("init: begin done");
		int bytesWritten = udp.write("hello");
		Serial.println("init: bytes written: " + String(bytesWritten));
		udp.endPacket();
		Serial.println("init: end done");
	}
//	Serial.println("initTmChannel done");
}

int EthernetUdpTmChannel::beginUdpPacket(uint16_t port) {
	Serial.println("beginUdpPacket entered, port: " + String(port));
	Serial.println("IP address: " + String(config.broadcastAddress[0]) + "." + String(config.broadcastAddress[1]) + "." + String(config.broadcastAddress[2]) + "." + String(config.broadcastAddress[3]));
	return udp.beginPacket(config.broadcastAddress, port);

}

void EthernetUdpTmChannel::sendPacket(const TelemetryPayload* const tmPayload) {
	Serial.println("sendPacket() entered");
	Serial.flush();
	//udp.write(tmPayload->getPayload(), tmPayload->getSize());
	udp.write("HELLO");
	Serial.println("udp.write done");
	Serial.flush();
	//int result = udp.endPacket();
	int result =1;
	udp.endPacket();
	Serial.println("udp endPacket done");
	if (result == 0) {
		Serial.println("Error in udp.endPacket()");
		Serial.flush();
	}
	Serial.println("udp.endPacket done");
	Serial.flush();
	//udp.stop();
}

void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload, RotorTelemetryProducer::TM_TYPE type) {
	const uint16_t port = BASE_PORT + type;
	Serial.println("output called with payload and type. Port: " + String(port));
	Serial.flush();

	if (udp.begin(udpServerPort) == 0) {
		Serial.println("Error beginning UDP: No sockets available");
	} else {
		Serial.println("UDP came up successfully.");
	}

	int result = udp.beginPacket(config.broadcastAddress, config.broadcastPort);
	Serial.flush();
	if (result == 0 ) {
		Serial.println("beginPacket failed!");
		udp.stop();
		return;
	} else {
		Serial.println("begin done");
	}
	int bytesWritten = udp.write(tmPayload->getPayload(), tmPayload->getSize());
	Serial.println(String(bytesWritten));
	Serial.flush();
	udp.endPacket();
	Serial.println("init: end done");
	Serial.flush();

//	if(beginUdpPacket(port) == 1) {
//		//Serial.println("calling sendPacket");
//		Serial.flush();
//		//sendPacket(tmPayload);
//		udp.write("HELLO");
//		udp.endPacket();
//
//	}
//	else {
//		Serial.println("[ERROR] - Could not create UDP packet with supplied remote ip and port");
//	}
}

void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload) {
	if (beginUdpPacket(config.broadcastPort) == 1) {
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
