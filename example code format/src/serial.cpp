#include <mbed.h>


int main() {

  	// put your setup code here, to run once:
	Serial pc(USBTX, USBRX); // Initialise serial with pc

	pc.printf("Hello World!\r\n"); // Print to pc once

	while(1) {
    	// put your main code here, to run repeatedly:
        pc.putc(pc.getc() + 1); // putc puts character into console; getc receives character you typed, idk what the +1 is
	}
}