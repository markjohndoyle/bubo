/*
 * CommandProcessor.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "Arduino.h"
#include "CommandProcessor.hpp"
#include "commands/BaseCommand.hpp"

namespace bubo {
namespace commanding {

using namespace commands;

const uint_fast8_t CommandProcessor::NUM_OF_FACTORIES;

CommandProcessor::CommandProcessor(CommandSource* commandSource)
	:  cmdSource(commandSource), commandInConstruction(false) {
}

CommandProcessor::~CommandProcessor() {
}

void CommandProcessor::processCommands() {
	byte inByte = cmdSource->getByte();
	// If there is not a command under construction by one of our factories then we treat the byte as a
	// command id and find out which factory to  use.
	if(!commandInConstruction) {
		for(int i = 0; i < CommandProcessor::NUM_OF_FACTORIES; i++) {
			if(commandFactories[i]->commandSupported(inByte)) {
				activeFactory = commandFactories[i];
				commandInConstruction = true;
				break;
			}
		}
	}
	else {
		activeFactory->buildCommand(inByte);
	}
}


void CommandProcessor::commandComplete(commands::BaseCommand* command) {
	commandInConstruction = false;
	command->execute();
}

void CommandProcessor::commandFailed(commands::BaseCommand* command) {
	commandInConstruction = false;
}


} /* namespace commanding */
} /* namespace bubo */
