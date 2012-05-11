/*
 * Command.hpp
 *
 *  Created on: May 11, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include "RotorCommand.hpp"
#include "bubo/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class RotorCommandW : public RotorCommand {
public:
	RotorCommandW(Rotor* targetRotor);

	~RotorCommandW();

	virtual bool processArgument(byte arg);

	virtual void execute() const;

private:
	long azimuth;
	long elevation;

	uint_fast8_t processedArgs;
};

}
}
}

#endif /* COMMAND_HPP_ */
