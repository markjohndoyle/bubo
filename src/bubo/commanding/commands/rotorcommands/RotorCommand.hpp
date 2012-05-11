/*
 * RotorCommand.hpp
 *
 *  Created on: 11 May 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORCOMMAND_HPP_
#define ROTORCOMMAND_HPP_

#include "bubo/commanding/commands/BaseCommand.hpp"

#include "bubo/Rotor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class RotorCommand: public BaseCommand {
public:
	RotorCommand(Rotor* targetRotor, uint16_t numOfArgs);

	virtual ~RotorCommand();

	virtual bool processArgument(byte arg) = 0;

	virtual void execute() const = 0;

protected:
	Rotor* rotor;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* ROTORCOMMAND_HPP_ */
