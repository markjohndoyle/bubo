/*
 * TelemetryPayload.hpp
 *
 *  Created on: 24 Mar 2012
 *      Author: Mark Doyle
 */

#ifndef TELEMETRYPAYLOAD_HPP_
#define TELEMETRYPAYLOAD_HPP_

#include "Arduino.h"

namespace bubo {

class TelemetryPayload {
	public:
		TelemetryPayload(byte* newPayload, size_t newPayloadSize) :
				payload(newPayload), size(newPayloadSize) {
		}

		~TelemetryPayload() {
			if(payload != 0) {
				free(payload);
			}
		}

		byte* getPayload() const {
			return payload;
		}

		size_t getSize() const {
			return size;
		}

	private:
		byte* payload;
		size_t size;
};
}

#endif /* TELEMETRYPAYLOAD_HPP_ */
