/*
 * CommandProcessor.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "Arduino.h"
#include "CommandProcessor.hpp"
#include "commands/BaseCommand.hpp"
#include "factories/RotorCommandFactory.hpp"
#include "bubo/rotor/Rotor.hpp"

namespace bubo {
namespace commanding {

using namespace commands;
using namespace factories;
using namespace rotor;

const uint_fast8_t CommandProcessor::NUM_OF_FACTORIES;

CommandProcessor::CommandProcessor(CommandSource* commandSource, Rotor* rotor)
	:  cmdSource(commandSource), commandInConstruction(false) {
	commandFactories[0] = new RotorCommandFactory(rotor);
}

CommandProcessor::~CommandProcessor() {
	for(int i = 0; i < CommandProcessor::NUM_OF_FACTORIES; i++) {
		CommandFactory* factory = commandFactories[i];
		delete factory;
	}
}

void CommandProcessor::processCommands() {
	int inByte = cmdSource->getData();
	// If we have some data check if there is a command under construction by one of our factories.
	// If there is then we treat the byte as a command id and find out which factory to  use.
	if(inByte != -1) {
		if(!commandInConstruction) {
//			Serial.println("No command under construction, finding factory....");
			for(int i = 0; i < CommandProcessor::NUM_OF_FACTORIES; i++) {
//				Serial.println("Checking factory " + String(i));
				if(commandFactories[i] == 0) {
					Serial.println("NULL POINTER @ Factory " + String(i));
					break;
				}
				if(commandFactories[i]->commandSupported((char)inByte)) {
//					Serial.println("Found a factory for id " + String(inByte));
					activeFactory = commandFactories[i];
					activeFactory->addListener(this);
					commandInConstruction = true;
					activeFactory->constructCommand(inByte);
					break;
				}
				else {
					Serial.println(String((char)inByte) + " not supported");
				}
			}
		}
		else {
//			Serial.println("Building command");
			activeFactory->buildCommand(inByte);
		}
	}
}


void CommandProcessor::commandComplete(commands::BaseCommand* command) {
//	Serial.println("Command executing....");
	commandInConstruction = false;
	command->execute();
	delete command;
}

void CommandProcessor::commandFailed() {
	commandInConstruction = false;
}


} /* namespace commanding */
} /* namespace bubo */
