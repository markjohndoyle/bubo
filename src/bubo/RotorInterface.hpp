/*
 * RotorInterface.hpp
 *
 *  Created on: 26 Mar 2012
 *      Author: Mark Doyle
 */
#ifndef ROTORINTERFACE_HPP_
#define ROTORINTERFACE_HPP_

#include "Arduino.h"

namespace bubo {

class RotorInterface {
	public:
		virtual long getCurrentAzimuth() const = 0;
		virtual long getCurrentElevation() const = 0;
};

}

#endif /* ROTORINTERFACE_HPP_ */
