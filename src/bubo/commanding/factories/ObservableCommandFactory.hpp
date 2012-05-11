/*
 * ObservableCommandFactory.hpp
 *
 *  Created on: May 10, 2012
 *      Author: Mark Doyle
 */

#ifndef OBSERVABLECOMMANDFACTORY_HPP_
#define OBSERVABLECOMMANDFACTORY_HPP_

#include "CommandFactory.hpp"
#include "CommandFactoryListener.hpp"

namespace bubo {
namespace commanding {
namespace factories {

class ObservableCommandFactory: public CommandFactory {
public:
	ObservableCommandFactory();
	virtual ~ObservableCommandFactory();

	virtual void buildCommand(byte data) = 0;

	virtual bool commandSupported(char id) = 0;

	void addListener(CommandFactoryListener* observer);

private:
	/**
	 * The factory listener. Currently we only support one listener.
	 */
	CommandFactoryListener* listener;

protected:
	/**
	 * When the command is complete the listener will be notified and passed the
	 * command under construction. Call this method when buildCommand has completed
	 * the command
	 */
	void commandComplete();

	/**
	 * When a command construction fails call this methods. CommandFactoryListeners will
	 * be notified.
	 */
	void commandConstructionFailed();
};

} /* namespace factories */
} /* namespace commanding */
} /* namespace bubo */
#endif /* OBSERVABLECOMMANDFACTORY_HPP_ */
