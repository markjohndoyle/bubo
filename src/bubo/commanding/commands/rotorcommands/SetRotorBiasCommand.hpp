/*
 * SetRotorBiasCommand.h
 *
 *  Created on: 12 May 2012
 *      Author: Mark Doyle
 */

#ifndef SETROTORBIASCOMMAND_H_
#define SETROTORBIASCOMMAND_H_

#include "RotorCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class SetRotorBiasCommand: public RotorCommand {
public:
	SetRotorBiasCommand(rotor::Rotor* targetRotor);

	virtual ~SetRotorBiasCommand();

	virtual bool processArgument(byte arg);

	virtual void execute() const;

private:
	long bias;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* SETROTORBIASCOMMAND_H_ */
