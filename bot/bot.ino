#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
OrangutanAnalog analog;
OrangutanLCD lcd;
OrangutanMotors motors;
OrangutanBuzzer buzzer;
OrangutanPushbuttons buttons;

unsigned int sensors[5]; // an array to hold sensor values
int timeout = 2000;

#include <avr/pgmspace.h>

const char hello[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";
const char twinkle[] PROGMEM = "L32O6 cr4cdcr4cdcrcdc";
const char doorbell[] PROGMEM = "L4O5 ec";
const char tune[] PROGMEM = "L16O5 cdMSeeMLdc4";
const char happy[] PROGMEM = "L16O5 MScececece";
const char jaws[] PROGMEM = "L32O3 bc";



const char hello_line1[] PROGMEM = "BETRAYAL";
const char hello_line2[] PROGMEM = "  BOT!  ";

// PINS
const int usb = 0;
//

// CONSTANTS
const int distanceThreshold = 2000;
//

int mode = 0;

void setup() {
	unsigned int counter; // used as a simple timer

	robot.init(timeout);

	lcd.printFromProgramSpace(hello_line1);
	lcd.gotoXY(0, 1);
	lcd.printFromProgramSpace(hello_line2);
	buzzer.playFromProgramSpace(hello);
	delay(1000);

	// Display on screen until start button is pressed.
	while (!buttons.isPressed(BUTTON_B)) {
		lcd.clear();
		lcd.print("PRESS B.");
		delay(100);
	}

	// Wait until you let go of the button so the 3pi doesn't start while you're still holding it.
	buttons.waitForRelease(BUTTON_B);
	delay(1000);

	pinMode(usb, INPUT);

	lcd.clear();
	while (buzzer.isPlaying()) {
		lcd.print("Go!");
	}
	buzzer.playFromProgramSpace(hello);

	lcd.clear();
	lcd.print(" INSERT ");
	lcd.gotoXY(0, 1);
	lcd.print(" PHONE! ");
}

void loop() {

	if (mode % 3 == 0) {
		welcome();
		if (phoneCheck() == 1) {
			mode++;

			lcd.clear();
			lcd.print(" I   <3 ");
			lcd.gotoXY(0, 1);
			lcd.print("CHARGING");

			buzzer.playFromProgramSpace(go);

		}

	} else if (mode % 3 == 1) {
		charge();
		if (reachCheck() == 1) {
			mode++;

			lcd.clear();
			lcd.print("NOOOoOOo");
			lcd.gotoXY(0, 1);
			lcd.print("OooOOoOO");
			buzzer.playFromProgramSpace(jaws);
		}
		if (phoneCheck() == 0) {
			mode += 2;

			lcd.clear();
			lcd.print(" INSERT ");
			lcd.gotoXY(0, 1);
			lcd.print(" PHONE! ");
		}
	} else {
		betray();
		if (phoneCheck() == 0) {
			mode++;

			lcd.clear();
			lcd.print(" INSERT ");
			lcd.gotoXY(0, 1);
			lcd.print(" PHONE! ");
		}
	}
}


void betray() {
	motors.setSpeeds(200, 200);
	buzzer.playFromProgramSpace(jaws);

	robot.readLineSensors(sensors);
	for (int i = 0; i < 5; i++) {
		if (sensors[i] >= timeout * .75) {

			motors.setSpeeds(-100, -100);
			delay(200);

			int r = random(2);
			if (r == 0) {
				motors.setSpeeds(-100, 100);
			} else {
				motors.setSpeeds(100, -100);
			}
			delay(random(500, 1500));
		}
	}
}

void charge() {
	buzzer.playFromProgramSpace(happy);

	motors.setSpeeds(30, 30);
	delay(5000);
	motors.setSpeeds(30, -30);
	delay(2500);

	robot.readLineSensors(sensors);
	for (int i = 0; i < 5; i++) {
		if (sensors[i] >= timeout * .75) {

			motors.setSpeeds(-30, -30);
			delay(200);

			int r = random(2);
			if (r == 0) {
				motors.setSpeeds(-30, 30);
			} else {
				motors.setSpeeds(30, -30);
			}
			delay(random(1000, 5000));
		}
	}

}

void welcome() {
	motors.setSpeeds(30, -30);
	delay(5000);
	motors.setSpeeds(0, 0);

	lcd.clear();
	lcd.print(" PRETTY ");
	lcd.gotoXY(0, 1);
	lcd.print(" PLEASE ");
	buzzer.playFromProgramSpace(twinkle);
	delay(3000);


	for (int i = 0; i <2; i++) {
		motors.setSpeeds(100, 100);
		delay(125);
		motors.setSpeeds(-50, -50);
		delay(250);
		motors.setSpeeds(0, 0);

		lcd.clear();
		lcd.print(" INSERT ");
		lcd.gotoXY(0, 1);
		lcd.print(" PHONE! ");
		buzzer.playFromProgramSpace(doorbell);
		delay(2000);
	}

	for (int i = 0; i < 3; i++) {
		motors.setSpeeds(50, 25);
		delay(1000);
		motors.setSpeeds(-25, -50);
		delay(1000);
	}
	motors.setSpeeds(0, 0);

	lcd.clear();
	lcd.print("I WANT 2");
	lcd.gotoXY(0, 1);
	lcd.print(" CHARGE ");
	buzzer.playFromProgramSpace(tune);
	delay(2000);
}

int phoneCheck() {
	int connection = digitalRead(usb);
	// HIGH is connected, LOW is disconnected.
	if (connection == HIGH) {
		return 1;
	} else {
		return 0;
	}
}

int reachCheck() {
	int distance = analog.readMillivolts(6);
	if (distance >= distanceThreshold) {
		return 1;
	} else {
		return 0;
	}
}
