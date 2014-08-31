#include <pololu/3pi.h>
#include <avr/pgmspace.h>

const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";

void initialize() {
	pololu_3pi_init(2000);

	print_from_program_space("BETRAYAL");
	lcd_goto_xy(0,1);
	print_from_program_space("BOT");
	play_from_program_space(welcome);
	delay_ms(1000);

	// Display on screen until start button is pressed.
	while (!button_is_pressed(BUTTON_B)) {
		clear();
		print("Press B");
		delay_ms(100);
	}

	// Wait until you let go of the button so the 3pi doesn't start while you're still holding it.
	wait_for_button_release(BUTTON_B);
	delay_ms(1000);

	// Auto-calibration for the sensors
	for (counter = 0; counter < 80; counter++) {

		if (counter < 20 || counter >= 60) {
			set_motors(40, -40);
		} else {
			set_motors(-40, 40)
		}

		// Keeps track of max and min values from the sensors
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);

	}
	set_motors(0, 0);

	clear();
	print("Go!");
	play_from_program_space(go);
	while(is_playing());
}

int main() {

	initialize();

	return 0;
}
