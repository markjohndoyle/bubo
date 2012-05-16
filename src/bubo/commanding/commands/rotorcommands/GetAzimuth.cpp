/*
 * GetAzimuth.cpp
 *
 *  Created on: 15 May 2012
 *      Author: mark
 */

#include "GetAzimuth.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

GetAzimuth::GetAzimuth(bubo::rotor::Rotor* targetRotor)
: RotorCommand(targetRotor, 0)
{
	Serial.println("GetAzimuth constructor");
	Serial.flush();
}

GetAzimuth::~GetAzimuth() {
	// TODO Auto-generated destructor stub
}

bool GetAzimuth::processArgument(byte arg) {
	return false;
}

void GetAzimuth::execute() const {
	long azimuth = rotor->getCurrentAzimuth();
	Serial.print("AZIMUTH DEGREES: ");Serial.println(azimuth);
	String a(azimuth);
	String out = "+0" + a; // FIXME
	Serial.println(out);
//	Serial.println("+0nnn");
//	Serial.flush();
}
} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
