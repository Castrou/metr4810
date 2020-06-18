#include <mbed.h>

#include "bt.h"
#include "motor.h"

bool check_bt_command( char *input) {
	
	return (input[0] == 'b' && input[1] == 't' && input[2] == ' ');
}

int main() {
	
	/* Variable Declaration */
	DigitalOut led(PA_0);
	DigitalOut ledToggle(PA_1);

	/* Driver Initialisation */
	motor_init();
	bt_init();

	/* Other Init */
	led = 0;

	while(1) {
		// if (bt_rxFlag()) {
		// 	/* BT Rx */
		// 	btVal = bt_read();
		// 	// bt_tx(btRx);
		// 	if (btVal == 0xFE) {
		// 		ledToggle = !ledToggle;
		// 	}
		// 	bt_clear_buffer();
		// }
		// led = !led;
		// wait_ms(10);
	}
}