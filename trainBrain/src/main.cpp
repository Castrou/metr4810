#include <mbed.h>

Serial bt(PA_2, PA_3, 9600);

int main() {
	// put your setup code here, to run once:
	char btInput = 0;
	DigitalOut led(PA_0);	// Declare led as DigitalOut at LED1 pin
	DigitalOut ledToggle(PA_1);
	led = 1;				// Turn LED on

	while(1) {
		// btInput = bt.getc();
        // bt.printf("RECV: %c\r\n", btInput);
        // if(btInput == 'o') {
        //     led = 1;
        // } else if (btInput == 'f') {
        //     led = 0;
        // }
		// btInput = 0;
		ledToggle = !(ledToggle);
		wait_ms(1000);
	}
}