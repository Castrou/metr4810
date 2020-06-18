/** 
 **************************************************************
 * @file host/lib/bt/bt.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>

#include "bt.h"
#include "serial.h"
// #include "cli.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Thread thread_bt;
RawSerial bt(D8_PIN, D2_PIN, 38400);
RawSerial btSlave(D8_PIN, D2_PIN, 38400);


// Circular buffers for serial TX and RX data - used by interrupt routines
const int buffer_size = 255;
// might need to increase buffer size for high baud rates
char btRx_buffer[buffer_size+1];
int btRx_buffPos = 0;

int btRxFlag = 0;

DigitalOut led(LED1);

/* Private function prototypes -----------------------------------------------*/
void bt_thread();
void bt_rx_interrupt();

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises CLI Thread
* @param  None
* @retval None
*/
void bt_init( void ) {

    bt.attach(&bt_rx_interrupt, RawSerial::RxIrq);
    // btSlave.attach(&bt_slave_interrupt, RawSerial::RxIrq);
    thread_bt.start(bt_thread);
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Sends to HC-05
* @param  None
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
        serial_print("%c", rx_char); // Show on console
        btRx_buffer[btRx_buffPos] = rx_char;
        btRx_buffPos++;

        if(rx_char == '\r') { // End of line
            btRx_buffPos = 0;
            btRxFlag = 1;
        }
    }
}

/*----------------------------------------------------------------------------*/

/**
* @brief  BT Thread - Process bluetooth RX info
* @param  None
* @retval None
*/
void bt_thread( void ) {

    while(1) {

        if (btRxFlag) {
            bt_clear_buffer();
        }
        thread_sleep_for(100);
    }
}

/*----------------------------------------------------------------------------*/
