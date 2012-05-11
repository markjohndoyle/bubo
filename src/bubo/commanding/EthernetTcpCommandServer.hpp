/*
 * EthernetTcpCommandServer.hpp
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDSERVER_H_
#define COMMANDSERVER_H_

#include "CommandSource.hpp"
#include "Ethernet/Ethernet.h"
#include "bubo/network/BuboEthernet.hpp"
#include "commands/BaseCommand.hpp"

namespace bubo {
namespace commanding {


class EthernetTcpCommandServer : public network::BuboEthernet, public CommandSource {
public:
	/** Default constructor uses telnet port as command server */
	EthernetTcpCommandServer();

	/** Allows construction of command server on a specified port */
	EthernetTcpCommandServer(uint16_t serverPort);

	~EthernetTcpCommandServer();

	/**
	 * Initialises the ethernet server. Must be called in the Arudino setup. You could call it in the loop but
	 * that would be odd. Basically, you can't have this in the constructor, too early.
	 */
	void initCmdServer();

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

};

}
}

#endif /* COMMANDSERVER_H_ */
