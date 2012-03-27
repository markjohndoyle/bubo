/*
 * TelemetryProducer.hpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 */

#ifndef TELEMETRYPRODUCER_HPP_
#define TELEMETRYPRODUCER_HPP_

#include "bubo/TelemetryPayload.hpp"
#include "bubo/RotorInterface.hpp"

namespace bubo {

class RotorTelemetryProducer {
	public:
		enum TM_TYPE {AZIMUTH, ELEVATION};

		RotorTelemetryProducer(RotorInterface* rotorInterface);

		TelemetryPayload produceTelemetry(TM_TYPE type);

	private:
		RotorInterface* rotor;
};

}

#endif /* TELEMETRYPRODUCER_HPP_ */
