/*
 * RotorCommandW.cpp
 *
 *  Created on: 11 May 2012
 *      Author: Mark Doyle
 */
#include "RotorCommandW.hpp"

namespace bubo {
namespace commanding {
namespace commands {

RotorCommandW::RotorCommandW(Rotor* targetRotor)
	: RotorCommand(targetRotor, 6), processedArgs(0) {
}

bool RotorCommandW::processArgument(byte arg) {
	bool result = false;

	return result;
}

void RotorCommandW::execute() const {

}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */

