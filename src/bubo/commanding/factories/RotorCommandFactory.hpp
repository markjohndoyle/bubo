/*
 * RotorCommandFactory.hpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORCOMMANDFACTORY_HPP_
#define ROTORCOMMANDFACTORY_HPP_

#include "ObservableCommandFactory.hpp"

namespace bubo {
// forward declare bubo::Rotor
class Rotor;
namespace commanding {
namespace factories {

class RotorCommandFactory : public ObservableCommandFactory {
public:
	RotorCommandFactory(Rotor* targetRotor);

	virtual ~RotorCommandFactory();

	void buildCommand(byte data);

	bool commandSupported(char id);

private:
	static const int NUM_OF_COMMANDS = 1;

	char commandIds[NUM_OF_COMMANDS];

	Rotor* rotor;

	/**
	 * Factory method for creating the concrete Rotor command. This is the only place that
	 * deals with concrete classes. New commands only need to be added here.
	 */
	void instantiateConcreteCommand(char id);
};

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
#endif /* ROTORCOMMANDFACTORY_HPP_ */
