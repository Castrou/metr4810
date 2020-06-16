/** 
 **************************************************************
 * @file trainBrain/lib/bt/bt.cpp
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RawSerial bt(PA_2, PA_3, 38400);

DigitalOut led1(PA_1);
// Circular buffers for serial TX and RX data - used by interrupt routines
const int buffer_size = BUFFER_SIZE;
// might need to increase buffer size for high baud rates
char btRx_buffer[buffer_size+1];
int btRx_buffPos = 0;

int btRxFlag = 0;

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
        btRx_buffer[btRx_buffPos] = rx_char;
        btRx_buffPos++;
    }

    btRxFlag = 1;
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Return btRxFlag
* @param  None
* @retval None
*/
bool bt_rxFlag( void ) {

    return btRxFlag;
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
