#include <mbed.h>

int main() {

	// put your setup code here, to run once:
	DigitalOut led(LED1);	// Declare led as DigitalOut at LED1 pin
	led = 1;				// Turn LED on

	while(1) {
		// put your main code here, to run repeatedly:
		led = !(led); 		// Invert current state
		wait_ms(1000);		// Wait 1 second
	}
}