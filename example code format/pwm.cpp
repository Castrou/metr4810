#include <mbed.h>

int main() {

	// put your setup code here, to run once:
	PwmOut pwm(LED1);
	pwm.period_ms(4);	// Set period to 4ms
	pwm.write(0.50f);	// Write 50% duty cycle
	float dutyCycle = 0.50;

	while(1) {
		// put your main code here, to run repeatedly:	Increases duty cycle up to 80% before resetting to 10%
		dutyCycle += 0.1;
		if(dutyCycle >= 0.9) {
			dutyCycle = 0.10;
		}
		pwm.write(dutyCycle);
		wait_ms(4);	
	}
}