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
	: RotorCommand(targetRotor, 6), processedArgs(0) {
	Serial.println("Instantiating YaesuCommandW!");
}

YaesuCommandW::~YaesuCommandW() {
}

bool YaesuCommandW::processArgument(byte arg) {
	bool result = false;

	// FIXME magic numbers in here. Linked to implementation of the YaesuRotor class.
	switch(processedArgs) {
			// first azimuth character
			case 0: {
				azimuth = (arg - 48) * 100;
				processedArgs++;
				result = true;
				break;
			}
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
				// first elevation character
			case 3: {
				elevation = (arg - 48) * 100;
				processedArgs++;
				result = true;
				break;
			}
			case 4: {
				elevation = elevation + (arg - 48) * 10;
				processedArgs++;
				result = true;
				break;
			}
				// last elevation character
			case 5: {
				elevation = elevation + (arg - 48);
				processedArgs++;
				azimuth = azimuth * 100;
				elevation = elevation * 100;
				result = true;
				break;
			}
			default: {
				// should never get here
				break;
			}
	}
	return result;
}

void YaesuCommandW::execute() const {
	Serial.println(String(rotor->getCurrentAzimuth()) + ":" + String(rotor->getCurrentElevation()));
	Serial.println("Executing YaesuCommandW - tarAz = " + String(azimuth) + " tarEz = " + String(elevation));
	rotor->setTargetAzimuth(azimuth);
	rotor->setTargetElevation(elevation);
}


bool YaesuCommandW::isComplete() const {
	return (processedArgs == (numOfArgs));
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */

