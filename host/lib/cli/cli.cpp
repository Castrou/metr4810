/** 
 **************************************************************
 * @file host/lib/cli/cli.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief CLI Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>
#include <stdarg.h>
#include <stdio.h>

#include "cli.h"
#include "bt.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Thread thread_cli;
RawSerial pc(USBTX,USBRX, 115200);

// Circular buffers for serial TX and RX data - used by interrupt routines
const int buffer_size = 255;
// might need to increase buffer size for high baud rates
char rx_buffer[buffer_size+1];
int rx_buffPos;

int rxFlag = 0;

/* Private function prototypes -----------------------------------------------*/
void cli_thread();
void cli_rx_interrupt();

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises CLI Thread
* @param  None
* @retval None
*/
void cli_init( void ) {

    pc.attach(&cli_rx_interrupt, RawSerial::RxIrq);
    thread_cli.start(cli_thread);
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Send information to the console
* @param  None
* @retval None
*/
void serial_print(const char *payload, ...) {

    char buffer[100];
    va_list argList;
    
    va_start(argList, payload);
    vsnprintf(buffer, 100, payload, argList);
	va_end(argList);

    pc.printf("%s", buffer);
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Clear RawSerial buffer
* @param  None
* @retval None
*/
void cli_clear_buffer( void ) {
    for(int i = 0; i < buffer_size; i++) {
        rx_buffer[i] = 0;
    }
}

/*----------------------------------------------------------------------------*/

/**
* @brief  CLI Interrupt for receive
* @param  None
* @retval None
*/
void cli_rx_interrupt( void ) {

    char rx_char;

    while(pc.readable()) {
        rx_char = pc.getc(); // Receive from buffer
        pc.putc(rx_char); // Show on console
        rx_buffer[rx_buffPos] = rx_char;
        rx_buffPos++;

        if(rx_char == '\r') { // End of line
            pc.putc('\n');      // Proper carriage return
            rx_buffer[rx_buffPos] = '\n';    // NULL terminate string
            rx_buffPos = 0;
            rxFlag = 1;
        }
    }

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Check if command
* @param  None
* @retval None
*/
bool cli_at_check( char *input ) {

    return (input[0] == 'A' && input[1] == 'T');
}

bool cli_bt_check( char *input ) {

    return (input[0] == 'b' && input[1] == 't' && input[2] == ' ');
}

/*----------------------------------------------------------------------------*/

/**
* @brief  CLI Thread - Process console serial input
* @param  None
* @retval None
*/
void cli_thread( void ) {

    DigitalOut led(LED1);
    
    while(1) {

        if (rxFlag) {
            if(cli_bt_check(rx_buffer)) {
                led = !led;
                bt_tx(rx_buffer);
                serial_print("%s", rx_buffer);
            } else if (cli_at_check(rx_buffer)) {
                bt_tx(rx_buffer);
            }
            cli_clear_buffer();
            rxFlag = 0;
        }

        thread_sleep_for(10);
    }
}

/*----------------------------------------------------------------------------*/
