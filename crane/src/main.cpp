#include "mbed.h"
#include "rtos.h"

#include "Pinduino.h"

#include "serial.h"
// #include "cli.h"
// #include "bt.h
#include "stepper.h"


int main()
{
    
    myserial_init();
    stepper_init();

    while(1);
}