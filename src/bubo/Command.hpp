/*
 * Command.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

namespace bubo {

/**
 * TODO currently only supports w commands. Basic design, not really extensible.
 */
class Command {
	public:
		enum CommandType {W};

		CommandType type;
		long azimuth;
		long elevation;

		Command(Command::CommandType cmdType, long azimuthIn, long elevationIn) {
			type = cmdType;
			azimuth = azimuthIn;
			elevation = elevationIn;
		}

};

}

#endif /* COMMAND_HPP_ */
