/*
 * RotorCommand.cpp
 *
 *  Created on: 11 May 2012
 *      Author: doylemr
 */

#include "RotorCommand.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace rotor;

RotorCommand::RotorCommand(Rotor* targetRotor, uint16_t numOfArgs)
	: BaseCommand(numOfArgs), rotor(targetRotor) {
}

RotorCommand::~RotorCommand() {
}


} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
