#include <mbed.h>


int main() {

  	// put your setup code here, to run once:
	DigitalOut led(LED1)    // Initialise LED pin to digital out
    led = 0;   // Start powered off

	while(1) {
    	// put your main code here, to run repeatedly:
		led = !(led);   // LED goes from 0 to 1 or vice versa **NOTE doing bitwise operations use ~(var) to signify 'not'
        wait_ms(1000);  // wait_ms instead of just wait cause ms > seconds dont @ me
	}
}