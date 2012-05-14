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
				payload(newPayload), size(newPayloadSize) {
		}

		~TelemetryPayload() {
			if (payload != 0) {
				free(payload);
			}
		}

		byte* getPayload() const {
			return payload;
		}

		size_t getSize() const {
			return size;
		}

		union Pack {
				struct {
						unsigned int id :sizeof(uint_fast8_t);
						unsigned int b :sizeof(long);
				} packed;
		};

	private:
		byte* payload;
		size_t size;
};
}

#endif /* TELEMETRYPAYLOAD_HPP_ */
