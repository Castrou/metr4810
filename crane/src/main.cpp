#include "mbed.h"
#include "rtos.h"

#include "Pinduino.h"

Thread thread_console;
Thread thread_bt;
Serial pc(USBTX,USBRX, 115200);
Serial bt(D8_PIN, D2_PIN, 9600);

DigitalOut led(LED1);

void console_thread() {
    led = 1;
    char input;

    while(1) {
        input = pc.getc();
        if(input == '\r') {
            pc.putc('\n');
        }
        pc.putc(input);
    }
}

void bt_thread() {

    while(1) {
        bt.printf("Yeet\r\n");
        thread_sleep_for(1000);
    }
}


int main()
{
    pc.printf("Hello World!\r\n");
    
    thread_bt.start(bt_thread);
    thread_console.start(console_thread);

    while(1);
}