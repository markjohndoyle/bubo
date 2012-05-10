/*
 * RotorCommandFactory.cpp
 *
 *  Created on: May 10, 2012
 *      Author: mark
 */

#include "RotorCommandFactory.hpp"

namespace bubo {
namespace commanding {
namespace factories {

const int RotorCommandFactory::NUM_OF_COMMANDS;

RotorCommandFactory::RotorCommandFactory() {
	commandIds[0] = 'w';
}

RotorCommandFactory::~RotorCommandFactory() {
	// TODO Auto-generated destructor stub
}


void RotorCommandFactory::buildCommand(byte data) {
}


bool RotorCommandFactory::commandSupported(char id) {
	bool result = false;
	for(int i = 0; i < NUM_OF_COMMANDS; i++) {
		char supportedId = commandIds[i];
		if(supportedId == id) {
			result = true;
			break;
		}
	}
	return result;
}


} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
