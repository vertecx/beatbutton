#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "config.h"

int main(void) {
	// Calculate the position of the most significant bit in the blink pattern.
	const int MSB = sizeof(unsigned int) * 8 - __builtin_clz(PATTERN) - 1;

	// Use Broadcom GPIO pin numbering scheme.
	wiringPiSetupGpio();

	// Configure button pin as an input with pull up.
	pinMode(BUTTON_PIN, INPUT);
	pullUpDnControl(BUTTON_PIN, PUD_UP);

	// Configure LED pin as an output defaulting to off.
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	// Initialize variables and start the infinite loop.
	int index = MSB, btnctr = 0;

	while (1) {
		if (digitalRead(BUTTON_PIN)) {
			// Button is not pressed so reset counter.
			btnctr = 0;

			// Write the value of the current bit in the blink pattern to the LED pin.
			digitalWrite(LED_PIN, (PATTERN >> index) & 1);

			// Calculate the next bit position.
			if (--index < 0) index = MSB;
		} else {
			// Turn off the LED. It will light up again when shutdown is commencing.
			digitalWrite(LED_PIN, LOW);

			// Break the infinite loop to shut down if the button has been pressed long enough.
			if (++btnctr > TICKS_BEFORE_SHUTDOWN) break;
		}

		delay(TICK_LENGTH);
	}

	// Turn on the shutdown light. It will stay lit until shutdown is complete.
	digitalWrite(LED_PIN, HIGH);
	return system("/sbin/shutdown -P now");
}
