/*
 * RotorCommandFactory.cpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#include "RotorCommandFactory.hpp"
#include "bubo/commanding/commands/rotorcommands/YaesuCommandW.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace factories {

using namespace commands;
using namespace rotor;

const int RotorCommandFactory::NUM_OF_COMMANDS;

RotorCommandFactory::RotorCommandFactory(Rotor* targetRotor)
	: rotor(targetRotor) {
	commandIds[0] = 'w';
}

RotorCommandFactory::~RotorCommandFactory() {
}

void RotorCommandFactory::buildCommand(byte data) {
	// If we are not currently constructing a command we must create the concrete rotor command.
	// else we pass the byte on as an argument and check if the command accepted it as valid.
	if (!commandUnderConstruction == 0) {
		bool ok = commandUnderConstruction->processArgument(data);
		if (!ok) {
			commandConstructionFailed();
			delete commandUnderConstruction;
			commandUnderConstruction = 0;
		}

		if(commandUnderConstruction->isComplete()){
			Serial.println("Command complete");
			commandComplete();
		}
	}
}

/**
 * This is the only place you need to alter when adding new rotor commands.
 */
void RotorCommandFactory::instantiateConcreteCommand(char id) {
	Serial.println("Supported! instantiating command");
	Serial.flush();
	if(commandUnderConstruction != 0) {
		delete commandUnderConstruction;
		commandUnderConstruction = 0;
	}

	if (id == 'w' || id == 'W') {
		commandUnderConstruction = new YaesuCommandW(rotor);
	}
}

bool RotorCommandFactory::commandSupported(char id) {
	Serial.println("checking support for id " + String(id));
	bool result = false;
	for (int i = 0; i < NUM_OF_COMMANDS; i++) {
		char supportedId = commandIds[i];
		if (supportedId == id) {
			instantiateConcreteCommand(id);
			result = true;
			break;
		}
	}
	return result;
}

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
