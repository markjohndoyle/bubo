/*
 * CommandServer.cpp
 *
 *  Created on: 9 May 2012
 *      Author: Mark Doyle
 */
#include "CommandServer.h"

using namespace bubo::commanding;
using namespace bubo::network;

CommandServer::CommandServer()
 : commandServer(EthernetServer(23)) {
	initCmdServer();
}

CommandServer::CommandServer(uint16_t serverPort)
	: commandServer(EthernetServer(serverPort)) {
	initCmdServer();
}

CommandServer::~CommandServer() {
}

void CommandServer::initCmdServer() {
	if(Ethernet.begin(MAC) == 0) {
		commandServer.begin();
	}
}

/**
 * Returns a String of Bubo's IP address.
 */
String CommandServer::ipToString() const {
	IPAddress ip = Ethernet.localIP();
	String ipStr;
	for (byte thisByte = 0; thisByte < 4; thisByte++) {
		// print the value of each byte of the IP address:
		ipStr += ip[thisByte];
		ipStr += ".";
	}
	return ipStr;
}

/**
 * Implementation simply returns the next byte in the stream.
 */
byte CommandServer::getByte() {
	byte byteIn = -1;
	client = commandServer.available();
	if(client) {
		if(client.available() > 0) {
			byteIn = client.read();
		}
	}
	return byteIn;
}


