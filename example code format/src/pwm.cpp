#include <mbed.h>


int main() {

  	// put your setup code here, to run once:
	PwmOut pwm(PC_8);   // Initialise Pin PC_8 to PWM Output

	pwm.period_ms(4);   // Period of 4ms
	pwm.write(0.25f);   // Duty Cycle (% of time high) of 25% (ie. 25% high, 75% low)

	while(1) {
    	// put your main code here, to run repeatedly:
        // No while required although you could change period/dutycycle here
	}
}