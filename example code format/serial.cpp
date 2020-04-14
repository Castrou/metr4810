#include <mbed.h>

int main() {

	// put your setup code here, to run once:
	Serial pc(USBTX, USBRX);		// Declare pc as Serial on USBTX and USBRX

	pc.printf("Hello World!\r\n");	// Print to console
	
	while(1) {
		// put your main code here, to run repeatedly:	Increases duty cycle up to 80% before resetting to 10%
		pc.putc(pc.getc() + 1);		// Print key presses to terminal
		
	}
}