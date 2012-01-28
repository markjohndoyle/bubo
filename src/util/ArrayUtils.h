/*
 * ArrayUtils.h
 *
 *  Created on: Nov 19, 2011
 *      Author: mark
 */

#ifndef ARRAYUTILS_H_
#define ARRAYUTILS_H_

#include <WProgram.h>

namespace util {

class ArrayUtils {

	private:
		ArrayUtils();
		virtual ~ArrayUtils();

	public:
		enum BASE {BASE_BYTE = 0, BASE_BIN = 2, BASE_OCT = 8, BASE_DEC = 10, BASE_HEX = 16};
		static void clearByteArray(byte byteArray[], int arraySize);
		static void newByteArray(const byte sourceArray[], const int createFromOffset, const int arrayLength, byte targetArray[]);
		static void dumpArray(const byte array[], const int offset, const int elementsToDump, const BASE base);
};

} /* namespace util */
#endif /* ARRAYUTILS_H_ */
