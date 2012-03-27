/**
 * Bubo - Yaesu ethernet rotor computer control interface
 *
 * Based upon work by Tom Doyle
 */
#include "Arduino.h"
#include <stdlib.h>
#include "SPI/SPI.h"
#include "Ethernet/Ethernet.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "bubo/RotorController.hpp"
#include "bubo/CommandProcessor.hpp"
#include "bubo/TelemetryPayload.hpp"
#include "bubo/TelemetryProducer.hpp"

static byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x8E, 0x5B };

/** The Ethernet Server that listens for commands */
EthernetServer commandServer(23);

/** The Ethernet Server that outputs TM. Connections are ignored */
EthernetServer tmServer(54780);

// TODO For future static assigned IP
/** Server IP */
IPAddress ip(192, 168, 0, 50);
/** Server network gateway */
IPAddress gateway(192, 168, 0, 1);
/** Server network subnet */
IPAddress subnet(255, 255, 240, 0);

EthernetClient client;

long previousRotorAzimuth = 0L; // previous rotor azimuth in degrees * 100
long previousRotorElevation = 0L; // previous rotor azimuth in degrees * 100

unsigned long rtcLastDisplayUpdate = 0UL; // rtc at start of last loop
unsigned long rtcLastRotorUpdate = 0UL; // rtc at start of last loop
unsigned long displayUpdateInterval = 500UL; // display update interval in mS
unsigned long rotorMoveUpdateInterval = 100UL; // rotor move check interval in mS

boolean azimuthMove = false; // azimuth move needed
boolean elevationMove = false; // elevation move needed

String azRotorMovement; // string for az rotor move display
String elRotorMovement; // string for el rotor move display

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
bubo::CommandProcessor commandProcessor;
bubo::RotorController rotorController;
bubo::RotorTelemetryProducer tmProducer(&rotorController);

/**
 * Returns a String of Bubo's IP address.
 */
String ipToString() {
	ip = Ethernet.localIP();
	String ipStr;
	for (byte thisByte = 0; thisByte < 4; thisByte++) {
		// print the value of each byte of the IP address:
		ipStr += ip[thisByte];
		ipStr += ".";
	}
	return ipStr;
}

void checkForCommand() {
	client = commandServer.available();

	if (client) {
		if (client.available() > 0) {
			char inByte = client.read();
			commandProcessor.decodeCommand(inByte);
		}
	}

	// Also check in serial interface. Good for development/debugging.
	// Ethernet and serial will interrupt each others commands!
	if (Serial.available() > 0) {
		char inSerialByte = Serial.read();
		commandProcessor.decodeCommand(inSerialByte);
	}
}

bool azLabelSet = false;
bool elLabelSet = false;
bool curAzDisplayed = false;
bool curElDisplayed = false;
long lastCurrentAz = -999;
long lastCurrentEl = -999;
long lastTargetAz = 0;
long lastTargetEl = 0;
size_t azDoubleStrLength = 0;
size_t elDoubleStrLength = 0;
String azLabel = "Az:";
String elLabel = "El:";
String arrow = "->";
int curAzCharLength = 0;
int curElCharLength = 0;

// FIXME Move to class.
void updateDisplay() {
	if (rotorController.isRotatingAzimuth()) {
		long curAz = rotorController.getCurrentAzimuth();
		long targetAz = rotorController.getTargetAzimuth();
		if (!azLabelSet) {
			lcd.clear();
			lcd.home();
			lcd.print(azLabel);
			azLabelSet = true;
		}
		if (curAz != lastCurrentAz) {
			lcd.setCursor(azLabel.length() + 1, 0);
			int curAzDouble = curAz / 100;
			curAzCharLength = curAzDouble / 10 + 1;
			lcd.print(curAzDouble);
			Serial.println(curAzDouble);
			Serial.println(azDoubleStrLength);
			lastCurrentAz = curAz;
			curAzDisplayed = true;
		}
		if (targetAz != lastTargetAz) {
			lcd.setCursor(azLabel.length() + curAzCharLength + 1, 0);
			lcd.print(arrow);
			double targetAzDouble = targetAz / 100;
			lcd.print(targetAzDouble);
			lastTargetAz = targetAz;
		}
	}
	else {
		lcd.home();
		if(azLabelSet) {
			lcd.print("                ");
			lcd.setCursor(0, 0);
			azLabelSet = false;
			lastCurrentAz = -9999;
		}
		lcd.print("Azimuth ok");
	}

	if (rotorController.isRotatingElevation()) {
		long curEl = rotorController.getCurrentElevation();
		long targetEl = rotorController.getTargetElevation();
		if (!elLabelSet) {
			lcd.setCursor(0, 1);
			lcd.print(elLabel);
			elLabelSet = true;
		}
		if (curEl != lastCurrentEl) {
			lcd.setCursor(elLabel.length() + 1, 1);
			int curElDouble = curEl / 100;
			curElCharLength = curElDouble / 10 + 1;
			lcd.print(curElDouble);
			lastCurrentEl = curEl;
		}
		if (targetEl != lastTargetEl) {
			lcd.setCursor(elLabel.length() + curAzCharLength + 1, 1);
			lcd.print(arrow);
			double targetElDouble = targetEl / 100;
			lcd.print(targetElDouble);
			lastCurrentEl = targetEl;
		}
	}
	else {
		lcd.setCursor(0, 1);
		if(elLabelSet) {
			lcd.print("                ");
			lcd.setCursor(0, 1);
			elLabelSet = false;
			lastCurrentEl = -9999;
		}
		lcd.print("Elevation ok");
	}
}

long previousAz = -99999;
void outputTelemetry() {
	// TODO nasty get azimuth from rotor for check; azimuth is also gathered by tm producer.
	long az = rotorController.getCurrentAzimuth();
	if (az != previousAz) {
		bubo::TelemetryPayload azTmPayload = tmProducer.produceTelemetry(bubo::RotorTelemetryProducer::AZIMUTH);
		tmServer.write(azTmPayload.getPayload(), azTmPayload.getSize());
		previousAz = az;
	}

	// TODO nasty get elevation from rotor for check; elevation is also gathered by tm producer.
	long el = rotorController.getCurrentElevation();
	if (el != previousAz) {
		bubo::TelemetryPayload elTmPayload = tmProducer.produceTelemetry(bubo::RotorTelemetryProducer::ELEVATION);
		tmServer.write(elTmPayload.getPayload(), elTmPayload.getSize());
		previousAz = az;
	}

}

/**
 * MAIN EVENT LOOP
 *
 * States:
 * 		1. Command phase.
 * 		2. Rotate phase.
 */
void loop() {
	checkForCommand();

	// get current elapsed time
	unsigned long elapsedTime = millis();

	// check for rtc overflow - skip this cycle if overflow
	// overflow if not true    _rotorMoveUpdateInterval
	if (elapsedTime > rtcLastDisplayUpdate) {
		// update rotor movement if necessary
		if (elapsedTime - rtcLastRotorUpdate > rotorMoveUpdateInterval) {
			rtcLastRotorUpdate = elapsedTime;
			rotorController.rotate();
		}
	}
	// rtc overflow - just in case
	else {
		// update rtcLast
		rtcLastDisplayUpdate = elapsedTime;
	}

	outputTelemetry();

	updateDisplay();
}

/**
 * Return bool true on success.
 */
bool setupEthernetServer() {
	// start the Ethernet connection:
	lcd.clear();
	lcd.print("Requesting IP");

	if (Ethernet.begin(mac) == 0) {
		lcd.clear();
		lcd.print("No IP from DHCP");
		return false;
	}

	commandServer.begin();
	tmServer.begin();

	// print local IP address to LCD screen.
	// TODO change from serial to LCD screen print.
	Serial.print("My IP address: ");
	Serial.println(ipToString());
	Serial.println();

	return true;
}

void setup() {
	bool error = false;

	lcd.init();
	lcd.backlight();
//	lcd.clear();
	delay(100);
	lcd.print("Bubo booting...");

	// initialise serial port:
	Serial.begin(9600);

	if (!setupEthernetServer()) {
		error = true;
	}

	commandProcessor.addCommandListener(&rotorController);

	if (!error) {
		lcd.clear();
		delay(100);
		lcd.print("Boot ok");
		lcd.setCursor(0, 1);
		lcd.print(ipToString());
	}

}

