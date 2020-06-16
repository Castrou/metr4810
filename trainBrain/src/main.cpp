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
	trainMotor.period_ms(20);

	while(1) {
		if (bt_rxFlag()) {
			/* BT Rx */
			btRx = bt_read();
			bt_tx(btRx);
			if (btRx[btIndex] == 'd') {
				ledToggle = 1;
				trainMotor.write(0.5f);
			} else if (btRx[btIndex] == 'o') {
				ledToggle = 0;
				trainMotor.write(0);
			}
			bt_clear_buffer();
		}
		led = !led;
		wait_ms(100);
	}
}