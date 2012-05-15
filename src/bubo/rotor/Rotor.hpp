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
		enum AZIMUTH_ROTATE {CLOCKWISE, ANTICLOCKWISE, STOP};

		virtual ~Rotor() {};

		virtual long getCurrentAzimuth() = 0;
		virtual long getCurrentElevation() = 0;

		virtual void setTargetAzimuth(long azimuth) = 0;
		virtual void setTargetElevation(long elevation) = 0;

		virtual void setRotateAzimuth(AZIMUTH_ROTATE rotationState) = 0;

		virtual void setBias(long newBias) = 0;

		virtual void setAzimuthZeroOffset(long offset) = 0;
};


} /* namespace rotor */
} /* namespace bubo */

#endif /* ROTORINTERFACE_HPP_ */
