/*
 * SerialCommandSource.h
 *
 *  Created on: 9 May 2012
 *      Author: doylemr
 */

#ifndef SERIALCOMMANDSOURCE_H_
#define SERIALCOMMANDSOURCE_H_

#include "CommandSource.hpp"

namespace bubo {
namespace commanding {

class SerialCommandSource : public CommandSource {
public:
	~SerialCommandSource();

	byte getByte();
};

} /* namespace commanding */
} /* namespace bubo */
#endif /* SERIALCOMMANDSOURCE_H_ */
