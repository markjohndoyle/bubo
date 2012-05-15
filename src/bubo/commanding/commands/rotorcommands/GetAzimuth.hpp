/*
 * GetAzimuth.hpp
 *
 *  Created on: 15 May 2012
 *      Author: mark
 */

#ifndef GETAZIMUTH_HPP_
#define GETAZIMUTH_HPP_

#include "RotorCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class GetAzimuth: public RotorCommand {

	public:
		GetAzimuth(bubo::rotor::Rotor* targetRotor);
		virtual ~GetAzimuth();
		bool processArgument(byte arg);
		void execute() const;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* GETAZIMUTH_HPP_ */
