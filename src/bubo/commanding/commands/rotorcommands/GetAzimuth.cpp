/*
 * GetAzimuth.cpp
 *
 *  Created on: 15 May 2012
 *      Author: mark
 */

#include "GetAzimuth.hpp"
#include "bubo/rotor/Rotor.hpp"
#include "bubo/rotor/YaesuRotor.hpp"

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
	long azimuth = rotor->getCurrentAzimuth() / bubo::rotor::YaesuRotor::SCALE_FACTOR;
	// FIXME round this!
	//Serial.print("AZIMUTH DEGREES: ");Serial.println(azimuth);
	String a(azimuth);

	for (int i = a.length(); i < 3; i++) {
		a = '0' + a;
	}
	String out = "+0" + a; // FIXME
	Serial.println(out);
//	Serial.println("+0nnn");
//	Serial.flush();
}
} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
