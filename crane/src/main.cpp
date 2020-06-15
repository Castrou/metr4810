#include "mbed.h"
#include "rtos.h"
#include "cli.h"
#include "Pinduino.h"

// #include "gripper.h"


// Thread thread_console;
// Thread thread_bt;
Thread thread_motor;

// Serial pc(USBTX,USBRX, 115200);
// Serial bt(D8_PIN, D2_PIN, 9600);

//DigitalOut led(LED1);
DigitalOut testout(D7_PIN);

DigitalOut dir(D2_PIN);
PwmOut stepper(D3_PIN);
// Gripper gripper(D3_PIN);

char input;
char line[30];


// void console_thread() {
//     int i = 0;

//     while(1) {
//         input = pc.getc();      // Receive input over serial
//         line[i] = input;
//         line[i] = 'a';
//         i++;
//         pc.putc(input);         // Display input
//         if(input == '\r') {
//             // bt.printf("command sent\r\n");
//             pc.putc('\n');      // Proper carriage return
//             line[i] = '\0';
//             // pc.printf("%s\r\n", line);
//             i = 0;
//         }
//     }
// }

// void bt_thread() {
//     char btInput;
//     while(1) {
//         btInput = bt.getc();
//         bt.printf("RECV: %c\r\n", btInput);
//         if(btInput == 'o') {
//             led = 1;
//             // gripper.release();
//             // gripper.pulsewidth(0.002f);
//             led = 0;
//         } else if (btInput == 'f') {
//             // gripper.grasp();
//             // gripper.pulsewidth(0.001f);
//         }
//         thread_sleep_for(1);
//     }
// }

void motor_thread() {
    // stepper.period_ms(2);
    // stepper.pulsewidth(0.001f);
    // dir = 1;
     while(1) {
         testout = 1;
         thread_sleep_for(1000);
         testout = 0;
         thread_sleep_for(1000);
    //     dir = 1;
    //     thread_sleep_for(1000);
    //     dir = 0;
    //     thread_sleep_for(1000);
    }
 }


int main()
{
    // serial_print(""");
    // thread_bt.start(bt_thread);
    // thread_console.start(console_thread);



    cli_init();


    thread_motor.start(motor_thread);

    while(1);
}