/*
 * ArrayUtils.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: Mark Doyle
 */

#include "ArrayUtils.h"

namespace util {

ArrayUtils::ArrayUtils() {
	// private; cannot instantiate utility class.
}

ArrayUtils::~ArrayUtils() {
	// private; cannot instantiate therefore cannot destroy utility class.
}

void ArrayUtils::clearByteArray(byte byteArray[], int arraySize) {
	// clear the received array
	for (int i = 0; i < arraySize; i++) {
		byteArray[i] = 0;
	}
}

void ArrayUtils::newByteArray(const byte sourceArray[], const int createFromOffset, const int arrayLength,
		byte targetArray[]) {
	for (int i = createFromOffset; i < arrayLength; i++) {
		targetArray[i] = sourceArray[i];
	}
}

void ArrayUtils::dumpArray(const byte array[], const int offset, const int elementsToDump, const BASE base) {
	Serial.println("--------- Array Dump ---------");
	for (int i = offset; i < elementsToDump; i++) {
		Serial.println(array[i], base);
	}
	Serial.println("------------------------------");
}

} /* namespace util */
