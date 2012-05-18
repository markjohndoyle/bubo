/*
 * RotorTelemetryProducer.hpp
 *
 *  Created on: 25 Mar 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORTELEMETRYPRODUCER_HPP_
#define ROTORTELEMETRYPRODUCER_HPP_

#include "TelemetryPayload.hpp"

#include <iterator> // must declare iterator befre vector in avr-stl
#include <vector>

namespace bubo {
namespace rotor {
	class Rotor;
}
namespace telemetry {

class TelemetryOutputChannel;

class RotorTelemetryProducer {
	public:
		enum TM_TYPE { POSITION };

		RotorTelemetryProducer(TelemetryOutputChannel* tmOutputChannel, rotor::Rotor* rotorInterface);
		RotorTelemetryProducer(std::vector<TelemetryOutputChannel*> tmOutputChannels, rotor::Rotor* rotorInterface);

		void sendTelemetry(TM_TYPE type) const;

	private:
		rotor::Rotor* rotor;

		static const uint8_t LAYOUT_ID_POSITION;

		std::vector<TelemetryOutputChannel*> outputChannels;

		TelemetryPayload* produceTelemetry(TM_TYPE type) const;
};

} /* namespace telemetry */
} /* namespace bubo */

#endif /* ROTORTELEMETRYPRODUCER_HPP_ */
