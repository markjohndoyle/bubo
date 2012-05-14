/*
 * NumericValueProcessor.h
 *
 *  Created on: 14 May 2012
 *      Author: mark
 */

#ifndef NUMERICVALUEPROCESSOR_H_
#define NUMERICVALUEPROCESSOR_H_

#include "ArgumentProcessor.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class NumericValueProcessor : public ArgumentProcessor {
	public:
		NumericValueProcessor(MODE byteMode);
		virtual ~NumericValueProcessor();

		virtual bool processArg(byte arg) = 0;

	private:
		long value;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* NUMERICVALUEPROCESSOR_H_ */
