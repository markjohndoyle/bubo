/*
 * SetUdpTmChannelBroadcastAdddress.hpp
 *
 *  Created on: 17 May 2012
 *      Author: Mark Doyle
 */

#ifndef SETUDPTMCHANNELBROADCASTADDDRESS_HPP_
#define SETUDPTMCHANNELBROADCASTADDDRESS_HPP_

#include "bubo/commanding/commands/BaseCommand.hpp"

namespace bubo {
namespace telemetry {
	class EthernetUdpTmChannel;
}
namespace commanding {
namespace commands {

class SetUdpTmChannelBroadcastAdddress: public BaseCommand {
	public:
		SetUdpTmChannelBroadcastAdddress(telemetry::EthernetUdpTmChannel* udpChannel);
		virtual ~SetUdpTmChannelBroadcastAdddress();

		bool processArgument(byte arg);

		void execute() const;

	private:
		telemetry::EthernetUdpTmChannel* channel;

		uint8_t firstOctet;
		uint8_t secondOctet;
		uint8_t thirdOctet;
		uint8_t fourthOctet;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* SETUDPTMCHANNELBROADCASTADDDRESS_HPP_ */
