/*
 * LcdDisplay.hpp
 *
 *  Created on: 12 May 2012
 *      Author: Mark Doyle
 */

#ifndef LCDDISPLAY_H_
#define LCDDISPLAY_H_

#include "Arduino.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"

namespace bubo {
namespace display {

class LcdDisplay {
	public:
		/*
		 * Set the LCD address to 0x27, 16, 2 for a 16 chars and 2 line display
		 */
		LcdDisplay();

		virtual ~LcdDisplay();

		void init();

		LiquidCrystal_I2C& getLcd();

	private:
		LiquidCrystal_I2C lcd;
};

} /* namespace display */
} /* namespace bubo */
#endif /* LCDDISPLAY_H_ */
