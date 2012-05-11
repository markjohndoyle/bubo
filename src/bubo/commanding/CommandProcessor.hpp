/*
 * CommandProcessor.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */

#ifndef COMMANDPROCESSOR_HPP_
#define COMMANDPROCESSOR_HPP_

#include "CommandSource.hpp"
#include "factories/CommandFactory.hpp"
#include "factories/CommandFactoryListener.hpp"

namespace bubo {
namespace commanding {

class CommandProcessor : public factories::CommandFactoryListener  {
	public:
		virtual ~CommandProcessor();

		CommandProcessor(CommandSource* commandSource);

		void processCommands();

		void commandComplete(commands::BaseCommand* command);

		void commandFailed(commands::BaseCommand* command);

	private:
		CommandSource* cmdSource;

		static const uint_fast8_t NUM_OF_FACTORIES = 2;

		factories::CommandFactory* commandFactories[NUM_OF_FACTORIES];

		factories::CommandFactory* activeFactory;

		bool commandInConstruction;
};

} /* namespace commanding */
} /* namespace bubo */

#endif /* COMMANDPROCESSOR_HPP_ */
