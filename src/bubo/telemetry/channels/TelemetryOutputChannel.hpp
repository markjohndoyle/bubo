/*
 * Channel.hpp
 *
 *  Created on: 16 May 2012
 *      Author: Mark Doyle
 */

#ifndef TELEMETRYOUTPUTCHANNEL_HPP_
#define TELEMETRYOUTPUTCHANNEL_HPP_

#include "bubo/telemetry/RotorTelemetryProducer.hpp"
#include "bubo/telemetry/TelemetryPayload.hpp"

namespace bubo {
namespace telemetry {

class TelemetryOutputChannel {
	public:
		virtual ~TelemetryOutputChannel() {};

		/**
		 * Send the telemetry payload using your chosen method.
		 * for example, as ascii over serial, in a udp packet, egal!
		 */
		virtual void output(const TelemetryPayload* const tmPayload) = 0;

		virtual void output(const TelemetryPayload* const tmPayload, RotorTelemetryProducer::TM_TYPE) = 0;

};

} /* namespace telemetry */
} /* namespace bubo */
#endif /* TELEMETRYOUTPUTCHANNEL_HPP_ */
