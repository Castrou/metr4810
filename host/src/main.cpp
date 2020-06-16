#include "mbed.h"
#include "rtos.h"

/* Utility includes */
#include "Pinduino.h"
/* Libraries */
// #include "cli.h"
#include "serial.h"
#include "bt.h"

int main() {
    
    /* Initialisation */
    // NOTE: Either cli for sending commands from computer or serial for controller
    // cli_init();
    myserial_init();
    bt_init();

    /* No need for loop - we running threads */
    while(1);
}