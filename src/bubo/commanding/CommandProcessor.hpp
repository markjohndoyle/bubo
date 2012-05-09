/*
 * CommandProcessor.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDPROCESSOR_HPP_
#define COMMANDPROCESSOR_HPP_

#include "CommandListener.hpp"
#include "CommandSource.h"

namespace bubo {
namespace commanding {

class CommandProcessor {
	public:
		CommandProcessor(CommandSource* commandSource);

		void addCommandListener(CommandListener* listener);

		void processCommands();

	private:
		CommandSource* cmdSource;

		// FIXME move to another class...struct at least. Violating SRP here.
		/** If a received byte is a char W or W then a gs232 w command is arriving */
		bool wCmdActive;
		/** If a w command is arriving we track the current byte position with this field */
		unsigned short wCmdCurrentBytePosition;
		/** As the w command arrives we populate this long value. */
		long wCmdAzArg;

		long wCmdElArg;

		CommandListener* cmdListener;

		void decodeCommand(char inChar);

		void processAzElNumeric(char character);
};

}
}

#endif /* COMMANDPROCESSOR_HPP_ */
