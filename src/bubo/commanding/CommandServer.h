/*
 * CommandServer.h
 *
 *  Created on: 9 May 2012
 *      Author: doylemr
 */

#ifndef COMMANDSERVER_H_
#define COMMANDSERVER_H_

#include "CommandSource.h"
#include "Ethernet/Ethernet.h"
#include "bubo/network/BuboEthernet.h"

namespace bubo {
namespace commanding {


class CommandServer : public network::BuboEthernet, public CommandSource {
public:
	/** Default constructor uses telnet port as command server */
	CommandServer();

	/** Allows construction of command server on a specified port */
	CommandServer(uint16_t serverPort);

	virtual ~CommandServer();

	/** Returns the servers ip as a string */
	String ipToString() const;

	byte getByte();

	const EthernetServer& getCommandServer() const {
		return commandServer;
	}

private:
	/** the command server */
	EthernetServer commandServer;

	/** the current client */
	EthernetClient client;

	void initCmdServer();
};

}
}

#endif /* COMMANDSERVER_H_ */
