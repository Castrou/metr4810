#include <mbed.h>

int main() {

  	// put your setup code here, to run once:
	DigitalOut led(LED1);
	DigitalIn usr_button(USER_BUTTON);
	led = 0;

	while(1) {
    	// put your main code here, to run repeatedly:
		if (usr_button) {
			led = 1; // Apparently this is press to disable LED
		} else {
			led = 0;
		}
		wait(1);
	}
}