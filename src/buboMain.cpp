/**
 * Bubo - Yaesu ethernet rotor computer control interface
 *
 */
#include "Arduino.h"
#include <stdlib.h>
#include "SPI/SPI.h"
#include "Ethernet/Ethernet.h"
#include "Ethernet/EthernetUdp.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "bubo/RotorController.hpp"
#include "bubo/commanding/CommandProcessor.hpp"
#include "bubo/TelemetryPayload.hpp"
#include "bubo/RotorTelemetryProducer.hpp"

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

bubo::commanding::CommandServer commandServer;
bubo::commanding::CommandProcessor tcpCommandProcessor(&commandServer);
bubo::commanding::SerialCommandSource serialCommandServer;
bubo::commanding::CommandProcessor serialCommandProcessor(&serialCommandServer);

bubo::RotorController rotorController;
bubo::RotorTelemetryProducer tmProducer(&rotorController);


void processCommands() {
	tcpCommandProcessor.processCommands();
	serialCommandProcessor.processCommands();
}

bool azLabelSet = false;
bool elLabelSet = false;
long lastCurrentAz = -999;
long lastCurrentEl = -999;
long lastTargetAz = -999;
long lastTargetEl = -999;
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
			lastCurrentAz = curAz;
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
		if (azLabelSet) {
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
		if (elLabelSet) {
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
//	long az = rotorController.getCurrentAzimuth();
//	if (az != previousAz) {
	bubo::TelemetryPayload azTmPayload = tmProducer.produceTelemetry(bubo::RotorTelemetryProducer::POSITION);
//		Serial.println(tmServer.remoteIP());
	IPAddress broadcast(192, 168, 0, 255);
	int check = tmServer.beginPacket(broadcast, 4023);
	if(check != 1) {
		Serial.println("[ERROR] - Could not create UDP packet with supplied remote ip and port");
		return;
	}
	tmServer.write(azTmPayload.getPayload(), azTmPayload.getSize());
	tmServer.endPacket();
//		previousAz = az;
//	}

}

bool checkForTmClient() {
	bool result = false;
	char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
	int packetSize = tmServer.parsePacket();
	if (tmServer.available()) {
		Serial.print("Received packet of size ");
		Serial.println(packetSize);
		Serial.print("From ");
		IPAddress remote = tmServer.remoteIP();
		for (int i = 0; i < 4; i++) {
			Serial.print(remote[i], DEC);
			if (i < 3) {
				Serial.print(".");
			}
		}
		Serial.print(", port ");
		Serial.println(tmServer.remotePort());

		// read the packet into packetBufffer
		tmServer.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
		Serial.println("Contents:");
		Serial.println(packetBuffer);
		result = true;
	}
	return result;
}

/**
 * MAIN EVENT LOOP
 *
 * States:
 * 		1. Command phase.
 * 		2. Rotate phase.
 */
void loop() {
	processCommands();

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


void setup() {
	bool error = false;

	lcd.init();
	lcd.backlight();
//	lcd.clear();
	delay(100);
	lcd.print("Bubo booting...");

	// initialise serial port:
	Serial.begin(9600);

	rotorController = bubo::RotorController();

	tcpCommandProcessor.addCommandListener(&rotorController);

	if (!error) {
		lcd.clear();
		delay(100);
		lcd.print("Boot ok");
		lcd.setCursor(0, 1);
//		lcd.print(ipToString());
	}

}

