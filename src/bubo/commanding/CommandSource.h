/*
 * CommandSource.h
 *
 *  Created on: 9 May 2012
 *      Author: doylemr
 */

#ifndef COMMANDSOURCE_H_
#define COMMANDSOURCE_H_

namespace bubo {
namespace commanding {

#include "Arduino.h"

class CommandSource {
public:
	virtual ~CommandSource();
	virtual byte getByte() = 0;
};

} /* namespace commanding */
} /* namespace bubo */
#endif /* COMMANDSOURCE_H_ */
