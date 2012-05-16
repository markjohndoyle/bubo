/*
 * EthernetUdpTmChannel.cpp
 *
 *  Created on: 9 May 2012
 *      Author: doylemr
 */

#include "EthernetUdpTmChannel.hpp"
#include "bubo/telemetry/TelemetryPayload.hpp"

namespace bubo {
namespace telemetry {

EthernetUdpTmChannel::EthernetUdpTmChannel()
	: udpServerPort(5478) {

}

EthernetUdpTmChannel::~EthernetUdpTmChannel() {
}


void EthernetUdpTmChannel::output(const TelemetryPayload* const tmPayload) {
}

} /* namespace telemetry */
} /* namespace bubo */
