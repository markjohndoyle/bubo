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
namespace rotor {

class Rotor {
	public:
		virtual ~Rotor() {};

		virtual long getCurrentAzimuth() const = 0;
		virtual long getCurrentElevation() const = 0;

		virtual void setTargetAzimuth(long azimuth) = 0;
		virtual void setTargetElevation(long elevation) = 0;

		virtual void setBias(long newBias) = 0;
};


} /* namespace rotor */
} /* namespace bubo */

#endif /* ROTORINTERFACE_HPP_ */
