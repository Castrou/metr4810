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
// #include "cli.h"
#include "serial.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Thread thread_bt;
RawSerial bt(D8_PIN, D2_PIN, 38400);


// Circular buffers for serial TX and RX data - used by interrupt routines
const int buffer_size = BUFFER_SIZE;
// might need to increase buffer size for high baud rates
char btRx_buffer[buffer_size];
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
    serial_print("BT Thread Initialising...\r\n");
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
        serial_print("%c", rx_char); // Show on console
        btRx_buffer[btRx_buffPos] = rx_char;
        btRx_buffPos++;
    }

    btRxFlag = 1;
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Read BT info
* @param  None
* @retval None
*/
char *bt_read( void ) {
    
    return btRx_buffer;
}

/*----------------------------------------------------------------------------*/

/**
* @brief  BT Thread - Process bluetooth RX info
* @param  None
* @retval None
*/
void bt_thread( void ) {

    // char *btRx;
    // btRx = (char *)malloc(sizeof(char)*BUFFER_SIZE);
    serial_print("BT Thread Initialised\r\n");
    while(1) {

        if (btRxFlag) {
            serial_print("BT Received: %s", btRx_buffer);
            bt_clear_buffer();
        }
        thread_sleep_for(10);
    }
}

/*----------------------------------------------------------------------------*/
