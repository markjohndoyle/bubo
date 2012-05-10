/*
 * BaseCommand.cpp
 *
 *  Created on: 9 May 2012
 *      Author: doylemr
 */

#include "BaseCommand.hpp"

using namespace bubo::commanding::commands;

uint16_t BaseCommand::getArgumentsLength() const {
	return argumentsLength;
}

void BaseCommand::setArgumentsLength(uint16_t argumentsLength) {
	this->argumentsLength = argumentsLength;
}

char BaseCommand::getCommandId() const {
	return commandId;
}

void BaseCommand::setCommandId(char commandId) {
	this->commandId = commandId;
}
 /* namespace bubo */
