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

ObservableCommandFactory::ObservableCommandFactory()
	: listener(0) {
}

ObservableCommandFactory::~ObservableCommandFactory() {
}

void ObservableCommandFactory::commandComplete() {
	if(listener != 0) {
		this->listener->commandComplete(commandUnderConstruction);
		commandUnderConstruction = 0;
	}
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
