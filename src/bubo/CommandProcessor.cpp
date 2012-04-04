/*
 * CommandProcessor.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "bubo/CommandProcessor.hpp"
#include "bubo/Command.hpp"
#include "Arduino.h"

using namespace bubo;

CommandProcessor::CommandProcessor() :
		wCmdActive(false), wCmdCurrentBytePosition(0) {
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
				this->cmdListener->acceptCommand(Command(Command::W, wCmdAzArg, wCmdElArg));
			}
			break;
		}
		default: {
			// should never get here
			break;
		}
	}
}

void CommandProcessor::addCommandListener(CommandListener* listener) {
	this->cmdListener = listener;
}
