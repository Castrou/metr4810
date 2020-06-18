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
#include "cli.h"
// #include "serial.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Thread thread_bt;
RawSerial btCrane(D8_PIN, D2_PIN, 38400);
RawSerial btTrain(D6_PIN, PB_11, 38400);


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

    btCrane.attach(&bt_rx_interrupt, RawSerial::RxIrq);
    // // btSlave.attach(&bt_slave_interrupt, RawSerial::RxIrq);
    serial_print("BT Thread Initialising...\r\n");
    thread_bt.start(bt_thread);

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Sends to HC-05
* @param  None
* @retval None
*/
void bt_tx( BTModule_t dest, char *payload ) {

    btCrane.printf(payload);
    // switch(dest) {
    //     case BT_CRANE:
    //         btCrane.putc(payload);
    //         break;

    //     case BT_TRAIN:
    //         btTrain.putc(payload);
    //         break;
    // }
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

    while (btCrane.readable()) {
        rx_char = btCrane.getc(); // Receive from buffer
        btRx_buffer[btRx_buffPos] = rx_char;
        btRx_buffPos++;
    }

    btRxFlag = 1;
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
