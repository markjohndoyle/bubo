/*
 * AutoCalibrate.hpp
 *
 *  Created on: 14 May 2012
 *      Author: mark
 */

#ifndef AUTOCALIBRATE_HPP_
#define AUTOCALIBRATE_HPP_

#include "RotorCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class AutoCalibrate : public RotorCommand {
	public:
		AutoCalibrate(rotor::Rotor* targetRotor);
		virtual ~AutoCalibrate();

		virtual bool processArgument(byte arg);

		virtual void execute() const;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* AUTOCALIBRATE_HPP_ */
