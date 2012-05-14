/*
 * YaesuRotor.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "YaesuRotor.hpp"
#include "utilEeprom/EEPROManything.hpp"

namespace bubo {
namespace rotor {

/** Base address in EEPROM to determine if a config exists at address CONFIG_EEPROM_ADDRESS */
const int YaesuRotor::CONFIG_STORED_FLAG = 0x01;

/** Base address in EEPROM to read or write the rotor config */
const int YaesuRotor::CONFIG_EEPROM_ADDRESS = 0x01;

const uint8_t YaesuRotor::PIN_EL_UP = 8;
const uint8_t YaesuRotor::PIN_EL_DOWN = 9;
const uint8_t YaesuRotor::PIN_AZ_LEFT = 6;
const uint8_t YaesuRotor::PIN_AZ_RIGHT = 5;
const uint8_t YaesuRotor::PIN_AZ_INPUT = A2;
const uint8_t YaesuRotor::PIN_EL_INPUT = A3;

const long YaesuRotor::MAX_AZIMUTH = 45000L;
const long YaesuRotor::MAX_ELEVATION = 18000L;

/**
 * Coefficient used to convert the analogue azimuth voltage into a degrees based upon the
 * Arduino's 10-bit ADC and the Rotor's maximum azimuth range.
 */
const long YaesuRotor::AZ_SCALE_FACTOR = 114;

/**
 * Coefficient used to convert the analogue elevation voltage into a degrees based upon the
 * Arduino's 10-bit ADC and the Rotor's maximum elevation range.
 */
const long YaesuRotor::EL_SCALE_FACTOR = 284;


YaesuRotor::YaesuRotor()
	: rotorMoveUpdateInterval(100UL), rotatingAzimuth(false), rotatingElevation(false) {

	// Rotor config defaults
	config.azimuthaAdZeroOffset = 0;
	config.elevationAdZeroOffset = 0;
	config.bias = 50;

	// Initialise digital pins for output.
	pinMode(PIN_EL_UP, OUTPUT);
	pinMode(PIN_EL_DOWN, OUTPUT);
	pinMode(PIN_AZ_LEFT, OUTPUT);
	pinMode(PIN_AZ_RIGHT, OUTPUT);

	allStop();

	// Get current position and set target to same value to prevent unnecessary rotation on startup.
	updateAzimuth();
	targetAzimuth = currentAzimuth;
	updateElevation();
	targetElevation = currentElevation;
}

YaesuRotor::~YaesuRotor() {
}

unsigned long YaesuRotor::getRotorMoveUpdateInterval() const {
	return rotorMoveUpdateInterval;
}

void YaesuRotor::setRotorMoveUpdateInterval(unsigned long rotorMoveUpdateInterval) {
	this->rotorMoveUpdateInterval = rotorMoveUpdateInterval;
}

void YaesuRotor::setTargetAzimuth(long azimuth) {
	targetAzimuth = azimuth;
}

void YaesuRotor::setTargetElevation(long elevation) {
	targetElevation = elevation;
}

void YaesuRotor::rotate() {
	// AZIMUTH
	// get current azimuth from G-5500
	updateAzimuth();
	// see if azimuth move is required
	if ((abs(currentAzimuth - targetAzimuth) > config.bias)) {
//			updateAzimuthMove();
		rotateAzimuth();
	}
	else {
		stopAzimuthRotor();
	}

	// ELEVATION
	// get current elevation from G-5500
	updateElevation();
	// see if an elevation move is required
	if (abs(currentElevation - targetElevation) > config.bias) {
//			updateElevationMove();
		rotateElevation();
	}
	else {
		stopElevationRotor();
	}
}

void YaesuRotor::rotateAzimuth() {
	// calculate rotor move
	long azDelta = targetAzimuth - currentAzimuth;
	// adjust move if necessary
	// adjust move if > 180 degrees
	if (azDelta > 18000) {
		azDelta = azDelta - 180;
	}
	else {
		// adjust move if < -180 degrees
		if (azDelta < -18000) {
			azDelta = azDelta + 18000;
		}
	}

	if (azDelta > 0) {
		rotatingAzimuth = true;
		digitalWrite(PIN_AZ_LEFT, LOW);
		digitalWrite(PIN_AZ_RIGHT, HIGH);
	}
	else {
		if (azDelta < 0) {
			rotatingAzimuth = true;
			digitalWrite(PIN_AZ_RIGHT, LOW);
			digitalWrite(PIN_AZ_LEFT, HIGH);
		}
	}
}

void YaesuRotor::rotateElevation() {
	// calculate rotor move
	long elDelta = targetElevation - currentElevation;

	if (elDelta > 0) {
		rotatingElevation = true;
		digitalWrite(PIN_EL_DOWN, LOW);
		digitalWrite(PIN_EL_UP, HIGH);
	}
	else {
		if (elDelta < 0) {
			rotatingElevation = true;
			digitalWrite(PIN_EL_UP, LOW);
			digitalWrite(PIN_EL_DOWN, HIGH);
		}
	}
}

void YaesuRotor::stopAzimuthRotor() {
	digitalWrite(PIN_AZ_LEFT, LOW);
	digitalWrite(PIN_AZ_RIGHT, LOW);
	rotatingAzimuth = false;
}

void YaesuRotor::stopElevationRotor() {
	digitalWrite(PIN_EL_UP, LOW);
	digitalWrite(PIN_EL_DOWN, LOW);
	rotatingElevation = false;
}


void YaesuRotor::allStop() {
	stopAzimuthRotor();
	stopElevationRotor();
}

void YaesuRotor::updateAzimuth() {
	long sensorValue = analogRead(PIN_AZ_INPUT);
	Serial.print("AZIMUTH VOLT: ");Serial.println(sensorValue);
	currentAzimuth = ((sensorValue * 10000) / AZ_SCALE_FACTOR) - config.azimuthaAdZeroOffset;
}

void YaesuRotor::updateElevation() {
	long sensorValue = analogRead(PIN_EL_INPUT);
	Serial.print("ELEVATION VOLT: ");Serial.println(sensorValue);
	currentElevation = (sensorValue * 10000) / EL_SCALE_FACTOR - config.elevationAdZeroOffset;
}

void YaesuRotor::setBias(long newBias) {
	this->config.bias = newBias;
}

int YaesuRotor::saveConfig() const {
	// write config to eeprom
	return EEPROM_writeAnything(CONFIG_EEPROM_ADDRESS, config);
}

int YaesuRotor::loadConfig() {
	// read config from eeprom and overwrite current config
	return EEPROM_readAnything(CONFIG_EEPROM_ADDRESS, config);
}


} /* namespace rotor */
} /* namespace bubo */
