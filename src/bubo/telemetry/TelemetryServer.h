/*
 * TelemetryServer.h
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#ifndef TELEMETRYSERVER_H_
#define TELEMETRYSERVER_H_

#include "Ethernet/EthernetUdp.h"
#include "bubo/network/BuboEthernet.h"

namespace bubo {
namespace telemetry {


class TelemetryServer : public bubo::network::BuboEthernet {
public:
	TelemetryServer();
	virtual ~TelemetryServer();

private:
	/** The UDP sender and receiver */
	EthernetUDP udp;

	/** Port the UDP listens for UDP client packets on */
	const uint16_t udpServerPort;

};

}
}

#endif /* TELEMETRYSERVER_H_ */
