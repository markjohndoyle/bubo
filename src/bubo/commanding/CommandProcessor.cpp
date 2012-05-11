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
	:  cmdSource(commandSource), commandInConstruction(false), wCmdActive(false), wCmdCurrentBytePosition(0) {
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


void CommandProcessor::addCommandListener(CommandListener* listener) {
	this->cmdListener = listener;
}


void CommandProcessor::decodeCommand(char inChar) {
	switch (inChar) {
		// gs232 W command
		case 'w':
		case 'W': {
			wCmdActive = true;
			wCmdCurrentBytePosition = 0;
			break;
		}
			// numeric - azimuth and elevation digits
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': {
			if (wCmdActive) {
				processAzElNumeric(inChar);
			}
			break;
		}
			// bubo information command
		case 'i': {
			break;
		}
		default: {
			// ignore everything else
			break;
		}
	}
}


void CommandProcessor::processAzElNumeric(char character) {
	switch (wCmdCurrentBytePosition) {
		// first azimuth character
		case 0: {
			wCmdAzArg = (character - 48) * 100;
			wCmdCurrentBytePosition++;
			break;
		}
		case 1: {
			wCmdAzArg = wCmdAzArg + (character - 48) * 10;
			wCmdCurrentBytePosition++;
			break;
		}
			// final azimuth character
		case 2: {
			wCmdAzArg = wCmdAzArg + (character - 48);
			wCmdCurrentBytePosition++;
			break;
		}
			// first elevation character
		case 3: {
			wCmdElArg = (character - 48) * 100;
			wCmdCurrentBytePosition++;
			break;
		}
		case 4: {
			wCmdElArg = wCmdElArg + (character - 48) * 10;
			wCmdCurrentBytePosition++;
			break;
		}
			// last elevation character
		case 5: {
			wCmdElArg = wCmdElArg + (character - 48);
			wCmdCurrentBytePosition++;
			wCmdAzArg = wCmdAzArg * 100;
			wCmdElArg = wCmdElArg * 100;
			Serial.println("Valid command assembled");
			if (cmdListener != 0) {
				Serial.println("Command accepted place holder - old code area. Being refactored");
//				this->cmdListener->acceptCommand(RotorCommandW(RotorCommandW::W, wCmdAzArg, wCmdElArg));
			}
			break;
		}
		default: {
			// should never get here
			break;
		}
	}
}

} /* namespace commanding */
} /* namespace bubo */
