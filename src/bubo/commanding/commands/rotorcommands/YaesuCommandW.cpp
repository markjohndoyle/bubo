/*
 * YaesuCommandW.cpp
 *
 *  Created on: 11 May 2012
 *      Author: Mark Doyle
 */
#include "YaesuCommandW.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace rotor;

YaesuCommandW::YaesuCommandW(Rotor* targetRotor)
	: RotorCommand(targetRotor, 7) {
}

YaesuCommandW::~YaesuCommandW() {
}

bool YaesuCommandW::processArgument(byte arg) {
	bool result = false;

	// FIXME magic numbers ASCII code numbers here. Just cast to int?
	switch(processedArgs) {
			// first azimuth character
			case 0: {
				azimuth = (arg - 48) * 100;
				processedArgs++;
				result = true;
				break;
			}
			// second azimuth character
			case 1: {
				azimuth = azimuth + (arg - 48) * 10;
				processedArgs++;
				result = true;
				break;
			}
			// final azimuth character
			case 2: {
				azimuth = azimuth + (arg - 48);
				processedArgs++;
				result = true;
				break;
			}
			// separator space
			case 3: {
				// ignore it
				processedArgs++;
				result = true;
				break;
			}
			// first elevation character
			case 4: {
				elevation = (arg - 48) * 100;
				processedArgs++;
				result = true;
				break;
			}
			case 5: {
				elevation = elevation + (arg - 48) * 10;
				processedArgs++;
				result = true;
				break;
			}
				// last elevation character
			case 6: {
				elevation = elevation + (arg - 48);
				processedArgs++;
				result = true;
				break;
			}
			default: {
				// should never get here. Do nothing and let result remain false.
				break;
			}
	}
	return result;
}

void YaesuCommandW::execute() const {
	rotor->setTargetAzimuth(azimuth);
	rotor->setTargetElevation(elevation);
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */

