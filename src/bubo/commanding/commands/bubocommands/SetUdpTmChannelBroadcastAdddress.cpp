/*
 * SetUdpTmChannelBroadcastAdddress.cpp
 *
 *  Created on: 17 May 2012
 *      Author: mark
 */

#include "SetUdpTmChannelBroadcastAdddress.hpp"

namespace bubo {
namespace commanding {
namespace commands {

using namespace telemetry;

SetUdpTmChannelBroadcastAdddress::SetUdpTmChannelBroadcastAdddress(EthernetUdpTmChannel* udpChannel)
	: BaseCommand(15) {
}

SetUdpTmChannelBroadcastAdddress::~SetUdpTmChannelBroadcastAdddress() {
}

bool SetUdpTmChannelBroadcastAdddress::processArgument(byte arg) {
	bool result = false;
	switch(processedArgs) {
		case 0: {
			result = true;
			processedArgs++;
			break;
		}
		case 1: {
			result = true;
			processedArgs++;
			break;
		}
		case 2: {
			result = true;
			processedArgs++;
			break;
		}
		case 3: {
			result = true;
			processedArgs++;
			break;
		}
		case 4: {
			result = true;
			processedArgs++;
			break;
		}
		case 5: {
			result = true;
			processedArgs++;
			break;
		}
		case 6: {
			result = true;
			processedArgs++;
			break;
		}
		case 7: {
			result = true;
			processedArgs++;
			break;
		}
		case 8: {
			result = true;
			processedArgs++;
			break;
		}
		case 9: {
			result = true;
			processedArgs++;
			break;
		}
		case 10: {
			result = true;
			processedArgs++;
			break;
		}
		case 11: {
			result = true;
			processedArgs++;
			break;
		}
		case 12: {
			result = true;
			processedArgs++;
			break;
		}
		case 13: {
			result = true;
			processedArgs++;
			break;
		}
		case 14: {
			result = true;
			processedArgs++;
			break;
		}
		case 15: {
			result = true;
			processedArgs++;
			break;
		}
	}
	return result;
}

void SetUdpTmChannelBroadcastAdddress::execute() const {
}

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
