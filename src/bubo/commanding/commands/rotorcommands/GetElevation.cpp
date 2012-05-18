#include "GetElevation.hpp"
#include "bubo/rotor/Rotor.hpp"
#include "bubo/rotor/YaesuRotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

GetElevation::GetElevation(bubo::rotor::Rotor* targetRotor)
: RotorCommand(targetRotor, 0)
{
	Serial.println("GetElevation constructor");
	Serial.flush();
}

GetElevation::~GetElevation() {
	// TODO Auto-generated destructor stub
}

bool GetElevation::processArgument(byte arg) {
	return false;
}

void GetElevation::execute() const {
	long Elevation = rotor->getCurrentElevation() / bubo::rotor::YaesuRotor::SCALE_FACTOR;
	// FIXME round this!
	//Serial.print("Elevation DEGREES: ");Serial.println(Elevation);
	String a(Elevation);

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
