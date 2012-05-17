/*
 * SetUdpTmChannelBroadcastAdddress.cpp
 *
 *  Created on: 17 May 2012
 *      Author: mark
 */

#include "SetUdpTmChannelBroadcastAdddress.hpp"
#include "IPAddress.h"
#include "bubo/telemetry/channels/EthernetUdpTmChannel.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace telemetry;

SetUdpTmChannelBroadcastAdddress::SetUdpTmChannelBroadcastAdddress(EthernetUdpTmChannel* udpChannel) :
		BaseCommand(15), channel(udpChannel) {
}

SetUdpTmChannelBroadcastAdddress::~SetUdpTmChannelBroadcastAdddress() {
}

/**
 * Format id full octet without stops.
 * e.g 192.168.0.1 should be sent as 192168000001
 *
 * TODO not very defensive.
 */
bool SetUdpTmChannelBroadcastAdddress::processArgument(byte arg) {
	bool result = false;

	// Get int value of ASCII numeric char.
	int8_t intValue = arg - 48;
	if (intValue > 0 || intValue < 9) {
		switch (processedArgs) {
			case 0: {
				firstOctet = intValue * 100;
				result = true;
				processedArgs++;
				break;
			}
			case 1: {
				firstOctet += intValue * 100;
				result = true;
				processedArgs++;
				break;
			}
			case 2: {
				firstOctet += intValue;
				result = true;
				processedArgs++;
				break;
			}
			case 3: {
				secondOctet = intValue * 100;
				result = true;
				processedArgs++;
				break;
			}
			case 4: {
				secondOctet = intValue * 10;
				result = true;
				processedArgs++;
				break;
			}
			case 5: {
				secondOctet = intValue;
				result = true;
				processedArgs++;
				break;
			}
			case 6: {
				thirdOctet = intValue * 100;
				result = true;
				processedArgs++;
				break;
			}
			case 7: {
				thirdOctet = intValue * 10;
				result = true;
				processedArgs++;
				break;
			}
			case 8: {
				thirdOctet = intValue;
				result = true;
				processedArgs++;
				break;
			}
			case 9: {
				fourthOctet = intValue * 100;
				result = true;
				processedArgs++;
				break;
			}
			case 10: {
				fourthOctet = intValue * 10;
				result = true;
				processedArgs++;
				break;
			}
			case 11: {
				fourthOctet = intValue;
				result = true;
				processedArgs++;
				break;
			}
		}
	}
	return result;
}

void SetUdpTmChannelBroadcastAdddress::execute() const {
	IPAddress address(firstOctet, secondOctet, thirdOctet, fourthOctet);
	channel->setBroadcastPort(address);
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
