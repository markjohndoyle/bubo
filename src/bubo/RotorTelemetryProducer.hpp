/*
 * RotorTelemetryProducer.hpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORTELEMETRYPRODUCER_HPP_
#define ROTORTELEMETRYPRODUCER_HPP_

#include "bubo/TelemetryPayload.hpp"
#include "bubo/Rotor.hpp"

namespace bubo {

class RotorTelemetryProducer {
	public:
		enum TM_TYPE { POSITION };

		RotorTelemetryProducer(Rotor* rotorInterface);

		TelemetryPayload produceTelemetry(TM_TYPE type);

	private:
		Rotor* rotor;

		static const uint8_t LAYOUT_ID_POSITION;
};

}

#endif /* ROTORTELEMETRYPRODUCER_HPP_ */
