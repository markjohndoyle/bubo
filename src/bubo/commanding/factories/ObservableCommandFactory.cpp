/*
 * ObservableCommandFactory.cpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#include "ObservableCommandFactory.hpp"

namespace bubo {
namespace commanding {
namespace factories {

ObservableCommandFactory::ObservableCommandFactory() {
}

ObservableCommandFactory::~ObservableCommandFactory() {
}

void ObservableCommandFactory::commandComplete() {
	this->listener->commandComplete(commandUnderConstruction);
	commandUnderConstruction = 0;
}

void ObservableCommandFactory::addListener(CommandFactoryListener* observer) {
	listener = observer;
}

void ObservableCommandFactory::commandConstructionFailed() {
	this->listener->commandFailed();
	commandUnderConstruction = 0;
}

}/* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
