/** 
 **************************************************************
 * @file btModule_commandline/lib/cli/cli.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief CLI Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void cli_init( void );
 * void serial_print( char *payload, ... );
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

const int buffer_size = BUFFER_SIZE;
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
    serial_print("CLI Thread Initialising...\r\n");
    thread_cli.start(cli_thread);
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Send information to the console
* @param  payload: payload to be sent to console (same format as printf)
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
            rxFlag = 1; // Received line
        }
    }

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Check if AT command
* @param  input: Received serial line
* @retval None
*/
bool cli_at_check( char *input ) {

    return (input[0] == 'A' && input[1] == 'T');
}

/*----------------------------------------------------------------------------*/

/**
* @brief  CLI Thread - Process console serial input
* @param  None
* @retval None
*/
void cli_thread( void ) {

    DigitalOut led(LED1);
    serial_print("CLI Thread Initialised\r\n");

    while(1) {

        if (rxFlag) {

            if (cli_at_check(rx_buffer)) { // AT command?
                bt_tx(rx_buffer); // Send to bluetooth module
            }

            cli_clear_buffer();
            rxFlag = 0;
        }

        thread_sleep_for(10);
    }
}

/*----------------------------------------------------------------------------*/
