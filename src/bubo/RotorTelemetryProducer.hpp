/*
 * RotorTelemetryProducer.hpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORTELEMETRYPRODUCER_HPP_
#define ROTORTELEMETRYPRODUCER_HPP_

#include "bubo/TelemetryPayload.hpp"

namespace bubo {

namespace rotor {
	class Rotor;
}

class RotorTelemetryProducer {
	public:
		enum TM_TYPE { POSITION };

		RotorTelemetryProducer(rotor::Rotor* rotorInterface);

		TelemetryPayload produceTelemetry(TM_TYPE type);

	private:
		rotor::Rotor* rotor;

		static const uint8_t LAYOUT_ID_POSITION;
};

}

#endif /* ROTORTELEMETRYPRODUCER_HPP_ */
