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
#include "factories/ObservableCommandFactory.hpp"

namespace bubo {
	namespace rotor {
		class Rotor;
	}  // namespace rotor
namespace commanding {

class CommandProcessor : public factories::CommandFactoryListener  {
	public:
		CommandProcessor(CommandSource* commandSource, rotor::Rotor* rotor);

		virtual ~CommandProcessor();

		void processCommands();

		void commandComplete(commands::BaseCommand* command);

		void commandFailed();

	private:
		CommandSource* cmdSource;

		static const uint_fast8_t NUM_OF_FACTORIES = 1;

		factories::ObservableCommandFactory* commandFactories[NUM_OF_FACTORIES];

		factories::ObservableCommandFactory* activeFactory;

		bool commandInConstruction;
};

} /* namespace commanding */
} /* namespace bubo */

#endif /* COMMANDPROCESSOR_HPP_ */
