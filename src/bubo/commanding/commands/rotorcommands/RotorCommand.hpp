/*
 * RotorCommand.hpp
 *
 *  Created on: 11 May 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORCOMMAND_HPP_
#define ROTORCOMMAND_HPP_

#include "bubo/commanding/commands/BaseCommand.hpp"

namespace bubo {
	namespace rotor {
		class Rotor;
	}
namespace commanding {
namespace commands {

class RotorCommand: public BaseCommand {
public:
	RotorCommand(rotor::Rotor* targetRotor, uint16_t numOfArgs);

	virtual ~RotorCommand();

	virtual bool processArgument(byte arg) = 0;

	virtual void execute() const = 0;

	virtual bool isComplete() const = 0;

protected:
	rotor::Rotor* rotor;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* ROTORCOMMAND_HPP_ */
