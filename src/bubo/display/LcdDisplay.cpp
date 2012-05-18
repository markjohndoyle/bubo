/*
 * LcdDisplay.cpp
 *
 *  Created on: 12 May 2012
 *      Author: Mark Doyle
 */

#include "LcdDisplay.hpp"

namespace bubo {
namespace display {

LcdDisplay::LcdDisplay()
	: lcd(LiquidCrystal_I2C(0x27, 16, 2)) {
}

LcdDisplay::~LcdDisplay() {
}

void LcdDisplay::init() {
	lcd.init();
	lcd.backlight();
	//	lcd.clear();
	delay(100);
}


LiquidCrystal_I2C& LcdDisplay::getLcd() {
	return lcd;
}

} /* namespace display */
} /* namespace bubo */
