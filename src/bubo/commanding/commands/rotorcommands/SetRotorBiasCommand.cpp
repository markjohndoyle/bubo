/*
 * SetRotorBiasCommand.cpp
 *
 *  Created on: 12 May 2012
 *      Author: Mark Doyle
 */

#include "SetRotorBiasCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace rotor;

SetRotorBiasCommand::SetRotorBiasCommand(Rotor* targetRotor)
	: RotorCommand(targetRotor, 3) {
}

SetRotorBiasCommand::~SetRotorBiasCommand() {
}

bool SetRotorBiasCommand::processArgument(byte arg) {
	bool result = false;

	return result;
}

void SetRotorBiasCommand::execute() const {
	rotor->setBias(bias);
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
