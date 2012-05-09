/*
 * BaseCommand.h
 *
 *  Created on: 9 May 2012
 *      Author: doylemr
 */

#ifndef BASECOMMAND_H_
#define BASECOMMAND_H_

#include "Arduino.h"

namespace bubo {
namespace commanding {
namespace commands {

class BaseCommand {

public:
	virtual ~BaseCommand();

	uint16_t getArgumentsLength() const;
	void setArgumentsLength(uint16_t argumentsLength);

	char getCommandId() const;
	void setCommandId(char commandId);

	virtual bool processArgument(byte arg) = 0;
	virtual void execute() = 0;


protected:
	char commandId;
	uint16_t argumentsLength;

};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* BASECOMMAND_H_ */
