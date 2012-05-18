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
const uint8_t YaesuRotor::PIN_AZ_LEFT = 5;
const uint8_t YaesuRotor::PIN_AZ_RIGHT = 6;
const uint8_t YaesuRotor::PIN_AZ_INPUT = A3;
const uint8_t YaesuRotor::PIN_EL_INPUT = A2;

const long YaesuRotor::MAX_AZIMUTH = 45000L;
const long YaesuRotor::MAX_ELEVATION = 18000L;

/**
 * Coefficient used to convert the analogue azimuth voltage into a degrees based upon the
 * Arduino's 10-bit ADC and the Rotor's maximum azimuth range.
 */
//const long YaesuRotor::AZ_SCALE_FACTOR = 98;

/**
 * Coefficient used to convert the analogue elevation voltage into a degrees based upon the
 * Arduino's 10-bit ADC and the Rotor's maximum elevation range.
 */
//const long YaesuRotor::EL_SCALE_FACTOR = 284;


YaesuRotor::YaesuRotor()
	: rotorMoveUpdateInterval(100UL), rotatingAzimuth(false), rotatingElevation(false) {

	// TODO check for saved config

	// Rotor config defaults
	config.configPresentFlag = 0xFF;
	config.azimuthaAdZeroOffset = 0;
	config.elevationAdZeroOffset = 0;
	config.bias = 5;

	// Initialise digital pins for output.
	pinMode(PIN_EL_UP, OUTPUT);
	pinMode(PIN_EL_DOWN, OUTPUT);
	pinMode(PIN_AZ_LEFT, OUTPUT);
	pinMode(PIN_AZ_RIGHT, OUTPUT);

	allStop();

	// Get current position and set target to same value to prevent unnecessary rotation on startup.
	targetAzimuth = getCurrentAzimuth();
	targetElevation = getCurrentElevation();
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
	targetAzimuth = azimuth * SCALE_FACTOR;
}

void YaesuRotor::setTargetElevation(long elevation) {
	targetElevation = elevation * SCALE_FACTOR;
}

void YaesuRotor::rotate() {
	// see if azimuth move is required
//	Serial.println("Bias = " + String(config.bias));
	if ((abs(getCurrentAzimuth() - targetAzimuth) > config.bias)) {
		rotateAzimuth();
	}
	else {
		stopAzimuthRotor();
	}

	// see if an elevation move is required
	if (abs(getCurrentElevation() - targetElevation) > config.bias) {
		rotateElevation();
	}
	else {
		stopElevationRotor();
	}
}

void YaesuRotor::rotateAzimuth() {
	// calculate rotor move
	Serial.println("Target Azimuth: " + String(targetAzimuth));
	Serial.println("Current Azimuth: " + String(getCurrentAzimuth()));
	long azDelta = targetAzimuth - getCurrentAzimuth();
	// adjust move if necessary
	// adjust move if > 180 degrees
//	if (azDelta > 180l * SCALE_FACTOR) {
//		azDelta = azDelta - 180l * SCALE_FACTOR;
//	}
//	else {
//		// adjust move if < -180 degrees
//		if (azDelta < -180l * SCALE_FACTOR) {
//			azDelta = azDelta + 180l * SCALE_FACTOR;
//		}
//	}

	if (azDelta > 0) {
		setRotateAzimuth(CLOCKWISE);
		Serial.println("AZ Going clockwise, delta: " + String(azDelta));
	}
	else if (azDelta < 0) {
		setRotateAzimuth(ANTICLOCKWISE);
		Serial.println("AZ Going counterclockwise, delta: " + String(azDelta));
	} else {
		stopAzimuthRotor();
	}
}

void YaesuRotor::rotateElevation() {
	// calculate rotor move
	Serial.println("Target Elevation: " + String(targetElevation));
	Serial.println("Current Elevation: " + String(getCurrentElevation()));
	long elDelta = targetElevation - getCurrentElevation();
	Serial.print("EL delta:");
	Serial.println(elDelta);



	if (elDelta > 0) {
		Serial.println("EL going UP, delta: " + String(elDelta));
		setRotateElevation(UP);
	}
	else if (elDelta < 0) {
		Serial.println("EL going DOWN, delta: " + String(elDelta));
		setRotateElevation(DOWN);
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

void YaesuRotor::setBias(long newBias) {
	this->config.bias = newBias;
}

void YaesuRotor::setAzimuthZeroOffset(long offset) {
	config.azimuthaAdZeroOffset = offset;
}

void YaesuRotor::setRotateAzimuth(AZIMUTH_ROTATE rotationState) {
	switch(rotationState) {
		case CLOCKWISE: {
			digitalWrite(PIN_AZ_LEFT, LOW);
			digitalWrite(PIN_AZ_RIGHT, HIGH);
			rotatingAzimuth = true;
			break;
		}
		case ANTICLOCKWISE: {
			digitalWrite(PIN_AZ_LEFT, HIGH);
			digitalWrite(PIN_AZ_RIGHT, LOW);
			rotatingAzimuth = true;
			break;
		}
		case STOP_AZ: {
			digitalWrite(PIN_AZ_LEFT, LOW);
			digitalWrite(PIN_AZ_RIGHT, LOW);
			rotatingAzimuth = false;
			break;
		}
	}
}

void YaesuRotor::setRotateElevation(ELEVATION_ROTATE rotationState) {
	switch(rotationState) {
		case (UP): {
			digitalWrite(PIN_EL_UP, HIGH);
			digitalWrite(PIN_EL_DOWN, LOW);
			rotatingElevation = true;
			break;
		}
		case (DOWN): {
			digitalWrite(PIN_EL_UP, LOW);
			digitalWrite(PIN_EL_DOWN, HIGH);
			rotatingElevation = true;
			break;
		}
		case (STOP_EL): {
			digitalWrite(PIN_EL_UP, LOW);
			digitalWrite(PIN_EL_DOWN, LOW);
			rotatingElevation = true;
			break;
		}
	}
}

bool YaesuRotor::saveSettings() {
	bool result = false;
	unsigned int bytesWritten = EEPROM_writeAnything(CONFIG_EEPROM_ADDRESS, config);
	if(bytesWritten == sizeof(rotorConfig)) {
		result = true;
	}
	else {
		// write failed, try and reset the config save flag just in case that was written.
		// this prevents future load calls from trying to load an undefined config.
		EEPROM.write(CONFIG_EEPROM_ADDRESS, 0x00);
	}
	return result;
}

bool YaesuRotor::loadSettings() {
	bool result = false;
	rotorConfig loadedConfig;
	// Check first byte for saved config flag
	uint8_t readByte = EEPROM.read(CONFIG_EEPROM_ADDRESS);

	// if we have a saved config read it in and load it into rotor config
	if(readByte == 0xFF) {
		// read config from eeprom and overwrite current config
		int bytesRead = EEPROM_readAnything<rotorConfig>(CONFIG_EEPROM_ADDRESS, loadedConfig);
		if(bytesRead == sizeof(rotorConfig)) {
			config = loadedConfig;
			result = true;
		}
	}

	return result;
}

long YaesuRotor::getCurrentAzimuth() {
	int sensorValue = analogRead(PIN_AZ_INPUT);
//	Serial.print("AZIMUTH VOLT: ");Serial.println(sensorValue);
	//	currentAzimuth = ((sensorValue * SCALE_FACTOR) / AZ_SCALE_FACTOR) + config.azimuthaAdZeroOffset;
	// y = (x-a)/(b-a) * (d-c) + c
	// Where
	// x = sensor value
	// y = angle
	// a = 409 i.e. lowest analogue value
	// b = 921 i.e. highest analogue value
	// c = 0 i.e. lowest degree 0 so can remove from equation
	// d = 450 i.e. highest degree
	//double azimuth = ((double)sensorValue - ADC_MIN_ROTOR_AZ) / (ADC_MAX_ROTOR_AZ - ADC_MIN_ROTOR_AZ) * MAX_ROTOR_AZ;
	double azimuth = (double)sensorValue * SCALE_FACTOR * MAX_ROTOR_AZ / ADC_MAX_ROTOR_AZ;
//	Serial.print("AZIMUTH: ");Serial.println(azimuth);
	return azimuth;
}


long YaesuRotor::getCurrentElevation() {
	int sensorValue = analogRead(PIN_EL_INPUT);
//	Serial.print("ELEVATION VOLT: ");Serial.println(sensorValue);
	//	currentElevation = (sensorValue * SCALE_FACTOR) / EL_SCALE_FACTOR + config.elevationAdZeroOffset;
	// y = (x-a)/(b-a) * (d-c) + c
	// Where
	// x = sensor value
	// y = angle
	// a = 409 i.e. lowest analogue value
	// b = 921 i.e. highest analogue value
	// c = 0 i.e. lowest degree 0 so can remove from equation
	// d = 180 i.e. highest degree
	//double elevation = ((double)sensorValue - ADC_MIN_ROTOR_EL) / (ADC_MAX_ROTOR_EL - ADC_MIN_ROTOR_EL) * MAX_ROTOR_EL;
	double elevation = (double)sensorValue * SCALE_FACTOR * MAX_ROTOR_EL / ADC_MAX_ROTOR_EL;
	return elevation;
}



} /* namespace rotor */
} /* namespace bubo */
