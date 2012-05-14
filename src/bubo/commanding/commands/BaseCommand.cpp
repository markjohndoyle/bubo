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

BaseCommand::BaseCommand(uint16_t numArgs)
	: numOfArgs(numArgs), processedArgs(0) {
}

BaseCommand::~BaseCommand() {
}

//bool BaseCommand::processArgument(byte arg) {
//	ArgumentProcessor* argProc = argumentProcessors[processedArgs];
//	if (argProc != 0) {
//		return argProc->processArg(arg);
//	}
//	else {
//		// No arg processors assumes all bytes are valid args for arg position "processedArgs"
//		return true;
//	}
//}

const bool BaseCommand::isComplete() const {
	return (processedArgs == numOfArgs);
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
