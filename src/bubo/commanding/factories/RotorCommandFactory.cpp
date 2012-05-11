/*
 * RotorCommandFactory.cpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#include "RotorCommandFactory.hpp"
#include "bubo/commanding/commands/rotorcommands/RotorCommandW.hpp"
#include "bubo/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace factories {

using namespace commands;

const int RotorCommandFactory::NUM_OF_COMMANDS;

RotorCommandFactory::RotorCommandFactory(Rotor* targetRotor) :
		rotor(targetRotor) {
	commandIds[0] = 'w';
}

RotorCommandFactory::~RotorCommandFactory() {
}

void RotorCommandFactory::buildCommand(byte data) {
	// If we are not currently constructing a command we must create the concrete rotor command.
	// else we pass the byte on as an argument and check if the command accepted it as valid.
	if (commandUnderConstruction == 0) {
		instantiateConcreteCommand(data);
	}
	else {
		bool ok = commandUnderConstruction->processArgument(data);
		if (!ok) {
			commandConstructionFailed();
		}
	}
}

/**
 * This is the only place you need to alter when adding new rotor commands.
 */
void RotorCommandFactory::instantiateConcreteCommand(char id) {
	if (id == 'w') {
		commandUnderConstruction = new RotorCommandW(rotor);
	}
}

bool RotorCommandFactory::commandSupported(char id) {
	bool result = false;
	for (int i = 0; i < NUM_OF_COMMANDS; i++) {
		char supportedId = commandIds[i];
		if (supportedId == id) {
			result = true;
			break;
		}
	}
	return result;
}

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
