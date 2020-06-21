/** 
 **************************************************************
 * @file btModule_commandline/lib/bt/bt.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void bt_init( void );
 * void bt_tx( char *payload );
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>

#include "bt.h"
#include "cli.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Thread thread_bt;
RawSerial bt(D8_PIN, D2_PIN, 38400);


const int buffer_size = BUFFER_SIZE;
char btRx_buffer[buffer_size];
int btRx_buffPos = 0;

int btRxFlag = 0;

/* Private function prototypes -----------------------------------------------*/
void bt_thread();
void bt_rx_interrupt();

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Bluetooth Thread
* @param  None
* @retval None
*/
void bt_init( void ) {

    bt.attach(&bt_rx_interrupt, RawSerial::RxIrq);
    serial_print("BT Thread Initialising...\r\n");
    thread_bt.start(bt_thread);

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Sends to HC-05
* @param  payload: Message to be sent to module
* @retval None
*/
void bt_tx( char *payload ) {

    bt.printf(payload);

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Clear RawSerial buffer
* @param  None
* @retval None
*/
void bt_clear_buffer( void ) {

    for(int i = 0; i < buffer_size; i++) {
        btRx_buffer[i] = 0;
    }

    btRx_buffPos = 0;
    btRxFlag = 0;
}

/*----------------------------------------------------------------------------*/

/**
* @brief  BT Interrupt for receive
* @param  None
* @retval None
*/
void bt_rx_interrupt( void ) {

    char rx_char;

    while (bt.readable()) {
        rx_char = bt.getc(); // Receive from buffer
        btRx_buffer[btRx_buffPos] = rx_char;
        btRx_buffPos++;
    }

    btRxFlag = 1; // Indicate something has been received
}

/*----------------------------------------------------------------------------*/

/**
* @brief  BT Thread - Process bluetooth RX info
* @param  None
* @retval None
*/
void bt_thread( void ) {

    serial_print("BT Thread Initialised\r\n");

    while(1) {

        if (btRxFlag) {
            serial_print("BT Received: %s\r\n", btRx_buffer); // Print received value
            bt_clear_buffer(); // Clear buffer
        }

        thread_sleep_for(10);
    }
}

/*----------------------------------------------------------------------------*/
