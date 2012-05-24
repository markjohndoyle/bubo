/*
 * TelemetryServer.h
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#ifndef TELEMETRYOUTPUTCHANNEL_H_
#define TELEMETRYOUTPUTCHANNEL_H_

#include "Ethernet/EthernetUdp.h"
#include "bubo/network/BuboEthernet.hpp"
#include "TelemetryOutputChannel.hpp"
#include "bubo/PersistentSettings.hpp"

namespace bubo {
namespace telemetry {

class TelemetryPayload;

class EthernetUdpTmChannel : public network::BuboEthernet, public TelemetryOutputChannel, public PersistentSettings {
public:
	EthernetUdpTmChannel();
	virtual ~EthernetUdpTmChannel();

	void output(const TelemetryPayload* const tmPayload);

	void output(const TelemetryPayload* const tmPayload, RotorTelemetryProducer::TM_TYPE);

	bool saveSettings();

	bool loadSettings();

	void setBroadcastAddress(IPAddress newAddress);

	void setBroadcastPort(uint16_t newPort);

	void initTmChannel();

private:
	/** The UDP sender and receiver */
	EthernetUDP udp;

	/** Port the UDP listens for UDP client packets on */
	const uint16_t udpServerPort;

	struct udpTmChannelConfig {
		IPAddress broadcastAddress;
		uint16_t broadcastPort;
	} config;

	int beginUdpPacket(uint16_t port);

	void sendPacket(const TelemetryPayload* const tmPayload);

	static const uint16_t BASE_PORT = 4023;

};

}
}

#endif /* TELEMETRYOUTPUTCHANNEL_H_ */
