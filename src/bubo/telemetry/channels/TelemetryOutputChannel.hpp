/*
 * Channel.hpp
 *
 *  Created on: 16 May 2012
 *      Author: mark
 */

#ifndef TELEMETRYOUTPUTCHANNEL_HPP_
#define TELEMETRYOUTPUTCHANNEL_HPP_

namespace bubo {
namespace telemetry {

class TelemetryPayload;

class TelemetryOutputChannel {
	public:
		virtual ~TelemetryOutputChannel() {};

		/**
		 * Send the telemetry payload using your chosen method.
		 * for example, as ascii over serial, in a udp packet, egal!
		 */
		virtual void output(const TelemetryPayload* const tmPayload) = 0;
};

} /* namespace telemetry */
} /* namespace bubo */
#endif /* TELEMETRYOUTPUTCHANNEL_HPP_ */
