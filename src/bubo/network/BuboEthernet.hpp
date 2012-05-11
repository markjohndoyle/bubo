/*
 * Buboe.h
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#ifndef BUBOETHERNET_H_
#define BUBOETHERNET_H_

#include "Arduino.h"
#include "SPI/SPI.h"

namespace bubo {
namespace network {

class BuboEthernet {
public:

protected:
	/** MAC address for the Ethernet shield */
	static uint8_t MAC[];

};

}

}

#endif /* BUBOETHERNET_H_ */
