/*
 * SerialCommandSource.cpp
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#include "SerialCommandSource.hpp"

namespace bubo {
namespace commanding {

SerialCommandSource::~SerialCommandSource() {

}

int SerialCommandSource::getData() {
	int inByte = -1;
	if(Serial.available() > 0) {
		inByte = Serial.read();
	}
	return inByte;
}

} /* namespace commanding */
} /* namespace bubo */
