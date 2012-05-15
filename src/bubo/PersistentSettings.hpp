/*
 * PersistentSettings.hpp
 *
 *  Created on: 15 May 2012
 *      Author: Mark Doyle
 */

#ifndef PERSISTENTSETTINGS_HPP_
#define PERSISTENTSETTINGS_HPP_

namespace bubo {

class PersistentSettings {
	public:
		virtual bool saveSettings() = 0;
};

} /* namespace bubo */


#endif /* PERSISTENTSETTINGS_HPP_ */
