/*
 * YaesuRotor.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Mark Doyle
 */

#ifndef ROTORCONTROLLER_HPP_
#define ROTORCONTROLLER_HPP_

#include "Arduino.h"
#include "Rotor.hpp"
#include "bubo/PersistentSettings.hpp"

namespace bubo {
namespace rotor {

/**
 * Conventions:
 * AZ or az = Azimuth
 * EL or el = Elevation
 */
class YaesuRotor : public Rotor, public PersistentSettings {
	public:
		YaesuRotor();
		~YaesuRotor();

		void rotate();

		void allStop();

		unsigned long getRotorMoveUpdateInterval() const;

		void setRotorMoveUpdateInterval(unsigned long newRotorMoveUpdateInterval);

		long getCurrentAzimuth();

		long getCurrentElevation();

		long getTargetAzimuth() const {
			return targetAzimuth;
		}

		long getTargetElevation() const {
			return targetElevation;
		}

		void setTargetAzimuth(long azimuth);

		void setTargetElevation(long elevation);

		long getAzimuthaAdZeroOffset() const {
			return this->config.azimuthaAdZeroOffset;
		}

		void setAzimuthaAdZeroOffset(long newOffset) {
			this->config.azimuthaAdZeroOffset = newOffset;
		}

		long getElevationAdZeroOffset() const {
			return this->config.elevationAdZeroOffset;
		}

		void setElevationAdZeroOffset(long newOffset) {
			this->config.elevationAdZeroOffset = newOffset;
		}

		bool isRotatingAzimuth() const {
			return this->rotatingAzimuth;
		}

		bool isRotatingElevation() const {
			return this->rotatingElevation;
		}

		void setBias(long newBias);

		void setRotateAzimuth(AZIMUTH_ROTATE rotationState);

		void setAzimuthZeroOffset(long offset);

		int loadConfig();

		bool saveSettings();

	private:
		/** The start address in EEPROM of the rotorconfiguration */
		static const int CONFIG_EEPROM_ADDRESS;
		static const int CONFIG_STORED_FLAG;

		/**
		 * 10 bit A/D converters in the Arduino have a max value of 1023
		 * for the azimuth the A/D value of 1023 should correspond to 450 degrees
		 * for the elevation the A/D value of 1023 should correspond to 180 degrees
		 * integer math is used so the scale value is multiplied by 100 to maintain accuracy
		 * the scale factor should be 100 * (1023 / 450) for the azimuth
		 * the scale factor should be 100 * (1023 / 180) for the elevation
		 */
		static const long AZ_SCALE_FACTOR;
		static const long EL_SCALE_FACTOR;

		/** elevation rotor up control line */
		static const byte PIN_EL_UP;
		/** elevation rotor down control line */
		static const byte PIN_EL_DOWN;
		/** azimuth rotor left control line */
		static const byte PIN_AZ_LEFT;
		/** azimuth rotor right control line */
		static const byte PIN_AZ_RIGHT;

		/** maximum rotor azimuth in degrees * 100 */
		static const long MAX_AZIMUTH;
		/** maximum rotor elevation in degrees * 100 */
		static const long MAX_ELEVATION;

		/** The analogue input pin used to receive the current rotor azimuth voltage */
		static const byte PIN_AZ_INPUT;
		/** The analogue input pin used to receive the current rotor elevation voltage */
		static const byte PIN_EL_INPUT;

		/** Current elevation as received by the rotor on PIN_ELEVATION */
		long currentElevation;
		/** Current elevation as received by the rotor on PIN_AZIMUTH */
		long currentAzimuth;

		unsigned long rotorMoveUpdateInterval;

		bool rotatingAzimuth;
		bool rotatingElevation;

		long targetAzimuth;
		long targetElevation;

		void updateAzimuth();

		void updateElevation();

		void stopAzimuthRotor();

		void stopElevationRotor();

		void rotateAzimuth();

		void rotateElevation();

		static const int ADC_MIN_ROTOR = 409;
		static const int ADC_MAX_ROTOR = 921;
		static const int MAX_ROTOR_AZ = 450;
		static const int MAX_ROTOR_EL = 180;

		struct rotorConfig {
			/** adjust to zero out lcd az reading when control box az = 0 */
			long azimuthaAdZeroOffset;
			/** adjust to zero out lcd el reading when control box el = 0 */
			long elevationAdZeroOffset;

			/**
			 * Tolerance for az-el match in rotor move in degrees * 100
			 * take care if you lower this value -  wear or dirt on the pots in your rotors
			 * or A/D converter jitter may cause hunting if the value is too low.
			 */
			long bias;
		} config;
};

} /* namespace rotor */
} /* namespace bubo */

#endif /* ROTORCONTROLLER_HPP_ */
