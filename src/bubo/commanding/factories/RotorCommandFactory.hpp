/*
 * RotorCommandFactory.hpp
 *
 *  Created on: May 10, 2012
 *      Author: mark
 */

#ifndef ROTORCOMMANDFACTORY_HPP_
#define ROTORCOMMANDFACTORY_HPP_

#include "ObservableCommandFactory.hpp"

namespace bubo {
namespace commanding {
namespace factories {

class RotorCommandFactory: public bubo::commanding::factories::ObservableCommandFactory {
public:
	RotorCommandFactory();
	virtual ~RotorCommandFactory();

	void buildCommand(byte data);

	bool commandSupported(char id);

private:
	static const int NUM_OF_COMMANDS = 1;
	char commandIds[NUM_OF_COMMANDS];
};

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
#endif /* ROTORCOMMANDFACTORY_HPP_ */
