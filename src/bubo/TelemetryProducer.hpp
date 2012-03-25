/*
 * TelemetryProducer.hpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 */

#ifndef TELEMETRYPRODUCER_HPP_
#define TELEMETRYPRODUCER_HPP_

#include "bubo/TelemetryPayload.hpp"

namespace bubo {

class TelemetryProducer {
	public:
		TelemetryProducer();

		TelemetryPayload produceTelemetry(long value);

	private:
		bool deltasOnly;
};

}

#endif /* TELEMETRYPRODUCER_HPP_ */
