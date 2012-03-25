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

//void displayAz(long az) {
//	// clear azimuth line
//	lcdSerial.print(line0, BYTE);
//	lcdSerial.print("                ");
//
//	//  adjust value for display
//	double azFloat = az;
//	azFloat = azFloat / 100.0;
//
//	// position lcd cursor on top line
//	lcdSerial.print(line0, BYTE);
//
//	// display azimuth
//	lcdSerial.print("AZ ");
//	// pad with spaces
//	if (azFloat < 10.0) {
//		lcdSerial.print(" ");
//	}
//	if (azFloat < 100.0) {
//		lcdSerial.print(" ");
//	}
//	lcdSerial.print(azFloat, 1);
//	lcdSerial.print(azRotorMovement);
//}

//void displayEl(long el) {
//	// clear elevation line  lcdSerial
//	lcdSerial.print(line1, BYTE);
//	lcdSerial.print("                ");
//
//	//  adjust value for display
//	double elFloat = el;
//	elFloat = elFloat / 100.0;
//
//	// position lcd cursor on bottom line
//	lcdSerial.print(line1, BYTE);
//
//	// display elevation
//	lcdSerial.print("EL ");
//	// pad with spaces
//	if (elFloat < 10.0) {
//		lcdSerial.print(" ");
//	}
//	if (elFloat < 100.0) {
//		lcdSerial.print(" ");
//	}
//	lcdSerial.print(elFloat, 1);
//	lcdSerial.print(elRotorMovement);
//}

void printIpToAllUserOuts() {
	String ip = ipToString();
	// to LCD Display
	lcd.clear();
	lcd.print("IP address:");
	lcd.setCursor(0, 1);
	lcd.print(ip);

	Serial.print("IP address:");
	Serial.println(ip);

	client.print("IP address:");
	client.println(ip);
	client.println();
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
long lastCurrentAz = 0;
long lastCurrentEl = 0;
long lastTargetAz = 0;
long lastTargetEl = 0;
size_t azDoubleStrLength = 0;
size_t elDoubleStrLength = 0;
String azLabel = "Az:";
String elLabel = "El:";
String arrow = "->";

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
		if (curAz != lastCurrentAz || !curAzDisplayed) {
			lcd.setCursor(azLabel.length() + 1, 0);
			double curAzDouble = curAz / 100;
			azDoubleStrLength = lcd.print(curAzDouble);
			lastCurrentAz = curAz;
			curAzDisplayed = true;
		}
		if (targetAz != lastTargetAz) {
			lcd.print(arrow);
			lcd.setCursor(azLabel.length() + arrow.length() + azDoubleStrLength + 1, 0);
			double targetAzDouble = targetAz / 100;
			lcd.print(targetAzDouble);
			lastTargetAz = targetAz;
		}
	}
	else {
		lcd.home();
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
		if (curEl != lastCurrentEl || !curElDisplayed) {
			lcd.setCursor(elLabel.length() + 1, 0);
			double curElDouble = curEl / 100;
			elDoubleStrLength = lcd.print(curElDouble);
			lastCurrentEl = curEl;
		}
		if (targetEl != lastTargetEl) {
			lcd.print(arrow);
			lcd.setCursor(elLabel.length() + arrow.length() + elDoubleStrLength + 1, 0);
			double targetElDouble = targetEl / 100;
			lcd.print(targetElDouble);
			lastCurrentEl = targetEl;
		}
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print("Elevation ok");
	}
}

union AzElUnion {
		unsigned long position;
		uint8_t bytes[4];
};

/**
 *
 */
bubo::TelemetryPayload createAzPayload(long az) {
//	Serial.println(az, DEC);
	// Create 4 byte array.
	byte* const bytes = (byte*) malloc(sizeof(long));
	if (bytes != NULL) {
		bytes[0] = az;
		bytes[1] = az >> 8;
		bytes[2] = az >> 16;
		bytes[3] = az >> 24;
	}
	else {
		Serial.println("Failed to allocate 4 bytes for TM");
	}

	return bubo::TelemetryPayload(bytes, 4);
}

/**
 *
 */
long previousAzValue = -999;
void outputTelemetry() {
	long az = rotorController.getCurrentAzimuth();
	if (previousAzValue != az) {
		bubo::TelemetryPayload azTmPayload = createAzPayload(az);
//		Serial.println("Payload binary out:");
//		Serial.write(azTmPayload.getPayload(), azTmPayload.getSize());
//		Serial.println();
//		Serial.println("-------------------");
		tmServer.write(azTmPayload.getPayload(), azTmPayload.getSize());
		previousAzValue = az;
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
	lcd.clear();
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

