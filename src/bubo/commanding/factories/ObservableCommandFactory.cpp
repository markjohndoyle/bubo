/*
 * ObservableCommandFactory.cpp
 *
 *  Created on: May 10, 2012
 *      Author: mark
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
}

void ObservableCommandFactory::commandConstructionFailed() {
	this->listener->commandFailed(commandUnderConstruction);
}

}/* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
