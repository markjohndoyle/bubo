/*
 * EEPROManything.hpp
 *
 *  Created on: 31 Mar 2012
 */

#ifndef EEPROMANYTHING_HPP_
#define EEPROMANYTHING_HPP_

#include "Arduino.h"
#include "EEPROM/EEPROM.h"


template<class T> int EEPROM_writeAnything(int eepromStartAddress, const T& value) {
	const byte* p = (const byte*) (const void*) &value;
	unsigned int i;
	for (i = 0; i < sizeof(value); i++) {
		EEPROM.write(eepromStartAddress++, *p++);
	}
	return i;
}

template<class T> int EEPROM_readAnything(int eepromStartAddress, T& value) {
	byte* p = (byte*) (void*) &value;
	unsigned int i;
	for (i = 0; i < sizeof(value); i++) {
		*p++ = EEPROM.read(eepromStartAddress++);
	}
	return i;
}

#endif /* EEPROMANYTHING_HPP_ */
