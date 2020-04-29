#include "mbed.h"
#include "rtos.h"

#include "Pinduino.h"

Thread thread_console;
Thread thread_bt;
Serial pc(USBTX,USBRX, 115200);
Serial bt(D8_PIN, D2_PIN, 9600);

DigitalOut led(LED1);

PwmOut gripper(D3_PIN);

char input;
char line[30];


void console_thread() {
    int i = 0;

    while(1) {
        input = pc.getc();      // Receive input over serial
        line[i] = input;
        line[i] = 'a';
        i++;
        pc.putc(input);         // Display input
        if(input == '\r') {
            // bt.printf("command sent\r\n");
            pc.putc('\n');      // Proper carriage return
            line[i] = '\0';
            // pc.printf("%s\r\n", line);
            i = 0;
        }
    }
}

void bt_thread() {
    char btInput;
    while(1) {
        btInput = bt.getc();
        bt.printf("RECV: %c\r\n", btInput);
        if(btInput == 'o') {
            led = 1;
            gripper.pulsewidth(0.002f);
            led = 0;
        } else if (btInput == 'f') {
            gripper.pulsewidth(0.001f);
        }
        thread_sleep_for(1);
    }
}


int main()
{
    gripper.period_ms(20);
    gripper.pulsewidth(0.0015f);
    pc.printf("Hello World!\r\n");
    
    thread_bt.start(bt_thread);
    thread_console.start(console_thread);

    while(1);
}