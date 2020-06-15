#include <mbed.h>

#include "bt.h"

bool check_bt_command( char *input) {
	
	return (input[0] == 'b' && input[1] == 't' && input[2] == ' ');
}

int main() {
	
	/* Variable Declaration */
	DigitalOut led(PA_0);
	DigitalOut ledToggle(PA_1);
	PwmOut trainMotor(PA_9);
	char *btRx;
	const int btIndex = 3;

	/* Driver Initialisation */
	bt_init();

	/* Other Init */
	btRx = (char *)malloc(sizeof(char)*BUFFER_SIZE);
	led = 0;

	while(1) {
		if (bt_rxFlag()) {
			/* BT Rx */
			bt_read(&btRx);
			if (btRx[btIndex] == 'd') {
				ledToggle = !ledToggle;
			}	
		}
		led = !led;
		wait_ms(100);
	}
}