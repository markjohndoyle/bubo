/*
 * BaseCommand.cpp
 *
 *  Created on: 11 May 2012
 *      Author: doylemr
 */
#include "BaseCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {


BaseCommand::BaseCommand(uint16_t numArgs) : numOfArgs(numArgs), processedArgs(0) {
}

BaseCommand::~BaseCommand() {
}

const bool BaseCommand::isComplete() const {
	return (processedArgs == numOfArgs);
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
