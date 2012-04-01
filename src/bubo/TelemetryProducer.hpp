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
		enum TM_TYPE { AZIMUTH, ELEVATION };

		RotorTelemetryProducer(RotorInterface* rotorInterface);

		TelemetryPayload produceTelemetry(TM_TYPE type);

	private:
		RotorInterface* rotor;

		static const uint8_t AZIMUTH_ID;
		static const uint8_t ELEVATION_ID;
};

}

#endif /* TELEMETRYPRODUCER_HPP_ */
