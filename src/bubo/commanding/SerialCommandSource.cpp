/*
 * SerialCommandSource.cpp
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#include "SerialCommandSource.h"

namespace bubo {
namespace commanding {

byte SerialCommandSource::getByte() {
	byte inByte = -1;
	if(Serial.available() > 0) {
		inByte = Serial.read();
	}
	return inByte;
}

} /* namespace commanding */
} /* namespace bubo */
