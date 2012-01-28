/*
 * ArrayUtilsTest.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: Mark Doyle
 */

#include "ArrayUtilsTest.h"

namespace test {

ArrayUtilsTest::~ArrayUtilsTest() {
	// TODO Auto-generated destructor stub
}

ArrayUtilsTest::ArrayUtilsTest() {
	// TODO Auto-generated constructor stub

}

void ArrayUtilsTest::testNewByteArray() {
	const int ARRAY_SIZE = 6;
	byte sourceArray[ARRAY_SIZE] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	byte targetArray[ARRAY_SIZE] = {0,	  0,	0,	  0,	0,	  0};

	util::ArrayUtils::newByteArray(sourceArray, 0, ARRAY_SIZE, targetArray);

	Serial.println(targetArray[0], HEX);
	Serial.println(targetArray[1], HEX);
	Serial.println(targetArray[2], HEX);
	Serial.println(targetArray[3], HEX);
	Serial.println(targetArray[4], HEX);
	Serial.println(targetArray[5], HEX);
}


int main(int argc, char **argv) {
	ArrayUtilsTest::testNewByteArray();

	return 0;
}


} /* namespace test */
