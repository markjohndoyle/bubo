/*
 * RotorCommandFactory.cpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#include "RotorCommandFactory.hpp"
#include "bubo/commanding/commands/rotorcommands/YaesuCommandW.hpp"
#include "bubo/commanding/commands/rotorcommands/SetRotorBiasCommand.hpp"
#include "bubo/commanding/commands/rotorcommands/GetAzimuth.hpp"
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
	commandIds[1] = 'W';
	commandIds[2] = 'b';
	commandIds[3] = 'B';
	commandIds[4] = 'c';
	commandIds[5] = 'C';

}

RotorCommandFactory::~RotorCommandFactory() {
}

void RotorCommandFactory::buildCommand(byte data) {
	// If we are not currently constructing a command we must create the concrete rotor command.
	// else we pass the byte on as an argument and check if the command accepted it as valid.
	if (!commandUnderConstruction == 0) {
		bool ok = commandUnderConstruction->processArgument(data);
		if (!ok) {
			Serial.println("Argument data " + String((char)data) + " invalid, command failed");
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
	else if (id == 'b' || id == 'B') {
		commandUnderConstruction = new SetRotorBiasCommand(rotor);
	}
	else if (id == 'c' || id == 'C') {
		commandUnderConstruction = new GetAzimuth(rotor);
	}
}

bool RotorCommandFactory::commandSupported(char id) {
	Serial.println("checking support for id " + String(id));
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

void RotorCommandFactory::constructCommand(char id) {
	instantiateConcreteCommand(id);
	if(commandUnderConstruction->isComplete()){
		Serial.println("Command complete");
		commandComplete();
	}
}

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
