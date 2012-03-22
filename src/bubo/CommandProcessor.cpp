/*
 * CommandProcessor.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "bubo/CommandProcessor.hpp"
#include "bubo/Command.hpp"

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
		case 0: // first azimuth character
		{
			wCmdAzArg = (character - 48) * 100;
			wCmdCurrentBytePosition++;
			break;
		}
		case 1: {
			wCmdAzArg = wCmdAzArg + (character - 48) * 10;
			wCmdCurrentBytePosition++;
			break;
		}
		case 2: // final azimuth character
		{
			wCmdAzArg = wCmdAzArg + (character - 48);
			wCmdCurrentBytePosition++;

//			// check for valid azimuth
//			if ((wCmdAzArg * 100) > maxRotorAzimuth) {
//				gs232WActive = false;
//				newAzimuth = 0L;
//				newElevation = 0L;
//			}
			break;
		}
		case 3: // first elevation character
		{
			wCmdElArg = (character - 48) * 100;
			wCmdCurrentBytePosition++;
			break;
		}
		case 4: {
			wCmdElArg = wCmdElArg + (character - 48) * 10;
			wCmdCurrentBytePosition++;
			break;
		}
		case 5: // last elevation character
		{
			wCmdElArg = wCmdElArg + (character - 48);
			wCmdCurrentBytePosition++;
//
//			// check for valid elevation
//			if ((wCmdElArg * 100) > maxRotorElevation) {
//				wCmdActive = false;
//				wCmdAzArg = 0L;
//				wCmdElArg = 0L;
//			}
//			else // both azimuth and elevation are ok
//			{
				// set up for rotor move
//				azimuthMove = true;
//				elevationMove = true;
				wCmdAzArg = wCmdAzArg * 100;
				wCmdElArg = wCmdElArg * 100;
				this->cmdListener->acceptCommand(Command(Command::W, wCmdAzArg, wCmdElArg));
//			}
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
