/*
 * ArgumentProcessor.hpp
 *
 *  Created on: 13 May 2012
 *      Author: Mark Doyle
 */

#ifndef ARGUMENTPROCESSOR_HPP_
#define ARGUMENTPROCESSOR_HPP_

#include "Arduino.h"

namespace bubo {
namespace commanding {
namespace commands {

class ArgumentProcessor {
	public:
		enum MODE {RAW, ASCII};

		ArgumentProcessor(MODE byteMode);
		virtual ~ArgumentProcessor();

		virtual bool processArg(byte arg) = 0;

	private:
		MODE mode;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* ARGUMENTPROCESSOR_HPP_ */
