#include <mbed.h>

#include "STM32FreeRTOS.h"

int main() {

  	// put your setup code here, to run once:
	PwmOut pwm(PC_8);
	DigitalIn button(USER_BUTTON);
	Serial pc(USBTX, USBRX);

	pc.printf("Hello World!\r\n");

	pwm.period_ms(4);
	pwm.write(0.25f);

	while(1) {
    	// put your main code here, to run repeatedly:
		if (button) {
			pc.printf("Button Pressed");
		}
	}
}