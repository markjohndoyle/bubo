/*
 * RotorController.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */
#include "bubo/RotorController.hpp"

using namespace bubo;

const uint8_t RotorController::PIN_EL_UP = 4;
const uint8_t RotorController::PIN_EL_DOWN = 5;
const uint8_t RotorController::PIN_AZ_LEFT = 8;
const uint8_t RotorController::PIN_AZ_RIGHT = 9;

const long RotorController::MAX_AZIMUTH = 45000L;
const long RotorController::MAX_ELEVATION = 18000L;

const long RotorController::AZ_SCALE_FACTOR = 227;
const long RotorController::EL_SCALE_FACTOR = 568;

const byte RotorController::PIN_AZ_INPUT = A14;
const byte RotorController::PIN_EL_INPUT = A15;

RotorController::RotorController() :
		azimuthaAdZeroOffset(325), elevationAdZeroOffset(0), bias(100), rotorMoveUpdateInterval(100UL), rotatingAzimuth(
				false), rotatingElevation(false) {

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
	if ((abs(currentAzimuth - targetAzimuth) > bias)) {
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
	if (abs(currentElevation - targetElevation) > bias) {
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
		targetAzimuth = cmd.azimuth;
		targetElevation = cmd.elevation;
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
	digitalWrite(PIN_EL_UP, LOW);
	digitalWrite(PIN_EL_DOWN, LOW);
	digitalWrite(PIN_AZ_LEFT, LOW);
	digitalWrite(PIN_AZ_RIGHT, LOW);
	rotatingAzimuth = false;
	rotatingElevation = false;
}

void RotorController::updateAzimuth() {
	long sensorValue = analogRead(PIN_AZ_INPUT);
	currentAzimuth = ((sensorValue * 10000) / AZ_SCALE_FACTOR) - azimuthaAdZeroOffset;
}

void RotorController::updateElevation() {
	long sensorValue = analogRead(PIN_EL_INPUT);
	currentElevation = (sensorValue * 10000) / EL_SCALE_FACTOR - elevationAdZeroOffset;
}

