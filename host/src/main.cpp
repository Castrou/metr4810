#include "mbed.h"
#include "rtos.h"

/* Utility includes */
#include "Pinduino.h"
/* Libraries */
#include "cli.h"
#include "bt.h"

int main() {
    
    /* Initialisation */
    cli_init();
    bt_init();

    /* No need for loop - we running threads */
    while(1);
}