/*
 * SetRotorBiasCommand.cpp
 *
 *  Created on: 12 May 2012
 *      Author: Mark Doyle
 */

#include "SetRotorBiasCommand.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace rotor;

SetRotorBiasCommand::SetRotorBiasCommand(Rotor* targetRotor)
	: RotorCommand(targetRotor, 3) {
}

SetRotorBiasCommand::~SetRotorBiasCommand() {
}

void SetRotorBiasCommand::execute() const {
	rotor->setBias(bias);
}

bool SetRotorBiasCommand::processArgument(byte arg) {
	bool result = false;

	int8_t intValue = arg - 48;

	switch(processedArgs) {
		case 0: {
			// push value up 10^2
			bias += intValue * 100;
			break;
		}
		case 1: {
			// push next byte up 10^1 and add to bias
			bias += intValue + 10;
			break;
		}
		case 2: {
			bias += intValue;
			break;
		}
	}

	return result;
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
