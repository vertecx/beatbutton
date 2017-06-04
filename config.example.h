// Specify the GPIO pins connected to the shutdown button and status LED.
// Uses BCM pin numbering described at http://wiringpi.com/pins/.
const int BUTTON_PIN = 23;
const int LED_PIN = 24;

// The tick length indicates how many milliseconds the program should delay at
// the end of each loop iteration.
// It is also the shortest duration the LED can be on or off.
const unsigned int TICK_LENGTH = 250;

// The pattern is a sequence of bits indicating how the LED should blink.
// If a bit is 1, the LED will be lit during that tick. A value of 0 will cause
// the LED to be off. The patterns will start with the most significant bit and
// then count down until the last bit before restarting with the MSB.
const unsigned int PATTERN = 0b1010000000000000000000000000;

// The tick length multiplied by ticks before shutdown is approximately how many
// milliseconds the power button must be pressed before shutdown is initiated.
const int TICKS_BEFORE_SHUTDOWN = 10;

/* BLINK PATTERN EXAMPLES
LED on 1 second, off 1 second. 3 second button press before shutdown:
	TICK_LENGTH = 1000
	PATTERN = 0b10
	TICKS_BEFORE_SHUTDOWN = 3

LED on 0.5 seconds, off 5.5 seconds. 4 second button press before shutdown:
	TICK_LENGTH = 500
	PATTERN = 0b100000000000
	TICKS_BEFORE_SHUTDOWN = 8

LED on 1 second, off 1 second, on 0.5 seconds, off 0.5 seconds, on 0.25 seconds,
off 0.25 seconds. 1 second button press before shutdown:
	TICK_LENGTH = 250
	PATTERN = 0b11110000110010
	TICKS_BEFORE_SHUTDOWN = 4
*/
