/*
 * CommandFactoryListener.hpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDFACTORYLISTENER_HPP_
#define COMMANDFACTORYLISTENER_HPP_

#include "bubo/commanding/commands/BaseCommand.hpp"

namespace bubo {
namespace commanding {
namespace factories {

class CommandFactoryListener {

public:
	virtual ~CommandFactoryListener() {};

	virtual void commandComplete(commands::BaseCommand* command) = 0;
	virtual void commandFailed() = 0 ;
};

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
#endif /* COMMANDFACTORYLISTENER_HPP_ */
