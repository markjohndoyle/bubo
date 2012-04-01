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
		TelemetryPayload(byte* newPayload, size_t newPayloadSize, uint8_t payloadId) :
				payload(newPayload), size(newPayloadSize), id(payloadId) {
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
		uint8_t id;
};
}

#endif /* TELEMETRYPAYLOAD_HPP_ */
