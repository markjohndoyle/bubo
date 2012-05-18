#ifndef GETELEVATION_HPP_
#define GETELEVATION_HPP_

#include "RotorCommand.hpp"

namespace bubo {
namespace commanding {
namespace commands {

class GetElevation: public RotorCommand {

	public:
		GetElevation(bubo::rotor::Rotor* targetRotor);
		virtual ~GetElevation();
		bool processArgument(byte arg);
		void execute() const;
};

} /* namespace commands */
} /* namespace commanding */
} /* namespace bubo */
#endif /* GETELEVATION_HPP_ */
