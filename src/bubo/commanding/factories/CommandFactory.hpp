/*
 * CommandFactory.hpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

#include "bubo/commanding/commands/BaseCommand.hpp"

namespace bubo {
namespace commanding {
namespace factories {

/**
 * Constructs commands given byte data. Currently supports reception of one byte at a time, i.e.
 * the buildCommand method expects a serial stream of bytes passed in sequence.
 */
class CommandFactory {
protected:
	/**
	 * The command this factory is currently constructing.
	 */
	bubo::commanding::commands::BaseCommand* commandUnderConstruction;

public:
	CommandFactory() : commandUnderConstruction(0) {}

	virtual ~CommandFactory() {}

	/**
	 * Instructs the factory to build the command given the next piece of data.
	 */
	virtual void buildCommand(byte data) = 0;

	/**
	 * Returns true or false depending upon whether the factory can build the
	 * command with the given id.
	 */
	virtual bool commandSupported(char id) = 0;

	virtual void constructCommand(char id) = 0;

};

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
#endif /* COMMANDFACTORY_H_ */
