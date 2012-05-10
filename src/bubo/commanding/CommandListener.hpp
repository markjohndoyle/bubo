/*
 * CommandListener.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDLISTENER_HPP_
#define COMMANDLISTENER_HPP_

#include "bubo/commanding/commands/BaseCommand.hpp"

namespace bubo {
namespace commanding {

class CommandListener {
	public:
		virtual ~CommandListener() {};

		virtual void acceptCommand(commands::BaseCommand* cmd) = 0;
};

}
}

#endif /* COMMANDLISTENER_HPP_ */
