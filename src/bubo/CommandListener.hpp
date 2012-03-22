/*
 * CommandListener.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: mark
 */

#ifndef COMMANDLISTENER_HPP_
#define COMMANDLISTENER_HPP_

#include "bubo/Command.hpp"

namespace bubo {

class CommandListener {
	public:
		virtual ~CommandListener() {};

		virtual void acceptCommand(Command cmd) = 0;
};

}

#endif /* COMMANDLISTENER_HPP_ */
