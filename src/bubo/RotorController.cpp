/*
 * RotorController.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "bubo/RotorController.hpp"
#include "utilEeprom/EEPROManything.hpp"

using namespace bubo;

const int RotorController::CONFIG_EEPROM_ADDRESS = 0;

const uint8_t RotorController::PIN_EL_UP = 8;
const uint8_t RotorController::PIN_EL_DOWN = 9;
const uint8_t RotorController::PIN_AZ_LEFT = 6;
const uint8_t RotorController::PIN_AZ_RIGHT = 5;

const long RotorController::MAX_AZIMUTH = 45000L;
const long RotorController::MAX_ELEVATION = 18000L;

const long RotorController::AZ_SCALE_FACTOR = 227;
const long RotorController::EL_SCALE_FACTOR = 568;

const byte RotorController::PIN_AZ_INPUT = A2;
const byte RotorController::PIN_EL_INPUT = A3;

RotorController::RotorController() : rotorMoveUpdateInterval(100UL), rotatingAzimuth(
				false), rotatingElevation(false) {

	config.azimuthaAdZeroOffset = 0;
	config.elevationAdZeroOffset = 0;
	config.bias = 200;

	pinMode(PIN_EL_UP, OUTPUT);
	pinMode(PIN_EL_DOWN, OUTPUT);
	pinMode(PIN_AZ_LEFT, OUTPUT);
	pinMode(PIN_AZ_RIGHT, OUTPUT);

	allStop();

	// Get current position and set target to same value to prevent unnecessary rotation on startup.
	updateAzimuth();
	targetAzimuth = currentAzimuth;
	Serial.println(targetAzimuth);
	updateElevation();
	targetElevation = currentElevation;
	Serial.println(targetElevation);
}

RotorController::~RotorController() {
}

unsigned long RotorController::getRotorMoveUpdateInterval() const {
	return rotorMoveUpdateInterval;
}

void RotorController::setRotorMoveUpdateInterval(unsigned long rotorMoveUpdateInterval) {
	this->rotorMoveUpdateInterval = rotorMoveUpdateInterval;
}

void RotorController::rotate() {
//	if (azimuthMove || elevationMove) {
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
//	}
//	else {
//		allStop();
//	}
}

void RotorController::rotateAzimuth() {
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
		Serial.print("AZ: ");Serial.println(currentAzimuth);
		Serial.print("TG: ");Serial.println(targetAzimuth);
		Serial.print("DL: ");Serial.println(azDelta);
		digitalWrite(PIN_AZ_LEFT, LOW);
		digitalWrite(PIN_AZ_RIGHT, HIGH);
	}
	else {
		if (azDelta < 0) {
			rotatingAzimuth = true;
			Serial.print("AZ: ");Serial.println(currentAzimuth);
			Serial.print("TG: ");Serial.println(targetAzimuth);
			Serial.print("DL: ");Serial.println(azDelta);
			digitalWrite(PIN_AZ_RIGHT, LOW);
			digitalWrite(PIN_AZ_LEFT, HIGH);
		}
	}
}

void RotorController::rotateElevation() {
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

void RotorController::stopAzimuthRotor() {
	digitalWrite(PIN_AZ_LEFT, LOW);
	digitalWrite(PIN_AZ_RIGHT, LOW);
	rotatingAzimuth = false;
}

void RotorController::stopElevationRotor() {
	digitalWrite(PIN_EL_UP, LOW);
	digitalWrite(PIN_EL_DOWN, LOW);
	rotatingElevation = false;
}

void RotorController::acceptCommand(Command cmd) {
	if (isCommandValid(cmd)) {
		targetAzimuth = cmd.azimuth ;
		targetElevation = cmd.elevation;
		Serial.println(targetAzimuth);
		Serial.println(targetElevation);
	}
}

bool RotorController::isCommandValid(Command cmd) {
	bool result = false;
	if (cmd.type == Command::W) {
		if (!(cmd.azimuth > MAX_AZIMUTH) && !(cmd.elevation > MAX_ELEVATION)) {
			result = true;
		}
	}
	return result;
}

void RotorController::allStop() {
	stopAzimuthRotor();
	stopElevationRotor();
}

void RotorController::updateAzimuth() {
	long sensorValue = analogRead(PIN_AZ_INPUT);
	currentAzimuth = ((sensorValue * 10000) / AZ_SCALE_FACTOR) - config.azimuthaAdZeroOffset;
}

void RotorController::updateElevation() {
	long sensorValue = analogRead(PIN_EL_INPUT);
//	Serial.print("VOLT: ");Serial.println(sensorValue);
	currentElevation = (sensorValue * 10000) / EL_SCALE_FACTOR;
}

int RotorController::saveConfig() const {
	// write config to eeprom
	return EEPROM_writeAnything(CONFIG_EEPROM_ADDRESS, config);
}

int RotorController::loadConfig() {
	// read config from eeprom and overwrite current config
	return EEPROM_readAnything(CONFIG_EEPROM_ADDRESS, config);
}
