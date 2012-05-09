/*
 * CommandListener.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDLISTENER_HPP_
#define COMMANDLISTENER_HPP_

#include "bubo/commanding/commands/Command.hpp"

namespace bubo {
namespace commanding {

class CommandListener {
	public:
		virtual ~CommandListener() {};

		virtual void acceptCommand(commands::Command cmd) = 0;
};

}
}

#endif /* COMMANDLISTENER_HPP_ */
