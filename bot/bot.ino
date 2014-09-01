#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
unsigned int sensors[5]; // an array to hold sensor values

#include <avr/pgmspace.h>

const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";

const char welcome_line1[] PROGMEM = "BETRAYAL";
const char welcome_line2[] PROGMEM = "   BOT  ";

void setup() {
	unsigned int counter; // used as a simple timer

	robot.init(2000);

	OrangutanLCD::printFromProgramSpace(welcome_line1);
	OrangutanLCD::gotoXY(0, 1);
	OrangutanLCD::printFromProgramSpace(welcome_line2);
	OrangutanBuzzer::playFromProgramSpace(welcome);
	delay(1000);

	// Display on screen until start button is pressed.
	while (!OrangutanPushbuttons::isPressed(BUTTON_B)) {
		OrangutanLCD::clear();
		OrangutanLCD::print("Press B");
		delay(100);
	}

	// Wait until you let go of the button so the 3pi doesn't start while you're still holding it.
	OrangutanPushbuttons::waitForRelease(BUTTON_B);
	delay(1000);

	// Auto-calibration for the sensors
	for (int counter = 0; counter < 80; counter++) {

		if (counter < 20 || counter >= 60) {
			OrangutanMotors::setSpeeds(40, -40);
		} else {
			OrangutanMotors::setSpeeds(-40, 40);
		}

		// Keeps track of max and min values from the sensors
		robot.calibrateLineSensors(IR_EMITTERS_ON);
		delay(20);

	}
	OrangutanMotors::setSpeeds(0, 0);

	OrangutanLCD::clear();
	OrangutanLCD::print("Go!");
	OrangutanBuzzer::playFromProgramSpace(go);
	while(OrangutanBuzzer::isPlaying());
}

void loop() {
	OrangutanMotors::setSpeeds(-100, 100);
}
