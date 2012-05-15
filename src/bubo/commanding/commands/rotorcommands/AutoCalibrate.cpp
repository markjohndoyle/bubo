/*
 * AutoCalibrate.cpp
 *
 *  Created on: 14 May 2012
 *      Author: mark
 */

#include "AutoCalibrate.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace rotor;

AutoCalibrate::AutoCalibrate(Rotor* targetRotor)
	: RotorCommand(targetRotor, 0) {
}

AutoCalibrate::~AutoCalibrate() {
}


bool AutoCalibrate::processArgument(byte arg) {
	return true;
}

void AutoCalibrate::execute() const {
	// rotate to maximum left.
	long lastAzimuth = rotor->getCurrentAzimuth();
	rotor->setRotateAzimuth(Rotor::ANTICLOCKWISE);
	bool notAtLimit = false;
	while(notAtLimit) {
		if(rotor->getCurrentAzimuth() == lastAzimuth) {
			notAtLimit = false;
		}
	}

	long azimuth = rotor->getCurrentAzimuth();
	if(azimuth != 0) {
//		rotor->setAzimuthZeroOffset(offset)
	}

}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
