/*
 * YaesuCommandW.hpp
 *
 *  Created on: May 11, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include "RotorCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class YaesuCommandW : public RotorCommand {
public:
	YaesuCommandW(rotor::Rotor* targetRotor);

	virtual ~YaesuCommandW();

	virtual bool processArgument(byte arg);

	virtual void execute() const;

private:
	long azimuth;
	long elevation;
};

}
}
}

#endif /* COMMAND_HPP_ */
