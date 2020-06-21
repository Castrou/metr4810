/** 
 **************************************************************
 * @file host/lib/serial/serial.cpp
 * @author Cameron Stroud - 44344968
 * @date 16062020
 * @brief Serial Task source file
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

#include "serial.h"
#include "bt.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    RX_WAITING,
    RX_RECEIVING,
    RX_TRANSMIT
} RxState_t;

typedef enum {
    BUTTON_VAL,
    L2_VAL,
    R2_VAL,
    LX_VAL,
    LY_VAL,
    RX_VAL,
    RY_VAL
};

/* Private define ------------------------------------------------------------*/
#define BYTE_LEN   7

#define PREAMBLE   0xFE
#define POSTAMBLE  0xFF

#define X_BUTTON            0b10000000
#define CIRCLE_BUTTON       0b01000000
#define TRIANGLE_BUTTON     0b00100000
#define SQUARE_BUTTON       0b00010000
#define L1_BUTTON           0b00001000
#define R1_BUTTON           0b00000100

#define AXIS_SIGN           0b10000000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Thread thread_serial;
RawSerial pc(USBTX,USBRX, 115200);

/* GAMEPAD VARIABLES */
uint8_t buttons = 0;
uint8_t l2 = 0;
uint8_t r2 = 0;
uint8_t lx = 0;
uint8_t ly = 0;
uint8_t rx = 0;
uint8_t ry = 0;
/*********************/

const int buffer_size = 255;

int rx_buffPos; // Position in packet
RxState_t rx_state; // Receiving state

int rxFlag = 0;

DigitalOut led1(LED1);

/* Private function prototypes -----------------------------------------------*/
void serial_thread();
void serial_rx_interrupt();

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Serial Thread
* @param  None
* @retval None
*/
void myserial_init( void ) {

    serial_print("Serial Thread Initialising...\r\n");
    rx_state = RX_WAITING;
    pc.attach(&serial_rx_interrupt, RawSerial::RxIrq);
    thread_serial.start(serial_thread);
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
void serial_clear_buffer( void ) {
    
    rxFlag = 0;
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Updates value based on packet position
* @param  None
* @retval None
*/
void update_val( uint8_t value, int pos ) {
    
    switch(pos) {
        case BUTTON_VAL:
            buttons = value;
            break;

        case L2_VAL:
            l2 = value;
            break;

        case R2_VAL:
            r2 = value;
            break;

        case LX_VAL:
            lx = value;
            break;
            
        case LY_VAL:
            ly = value;
            break;

        case RX_VAL:
            rx = value;
            break;

        case RY_VAL:
            ry = value;
            break;
    }
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Serial Interrupt for receive
* @param  None
* @retval None
*/
void serial_rx_interrupt( void ) {

    led1 = !led1;
    uint8_t rx_byte;

    while(pc.readable()) {
        /* Rx Finite State Machine */
        switch(rx_state) {
            case RX_WAITING: // Waiting on packet
                rx_byte = pc.getc();
                if (rx_byte == PREAMBLE) {
                    // oh yeah its receive time bb
                    rx_state = RX_RECEIVING;
                }
                break;

            case RX_RECEIVING: // Received preamble: packet building time
                rx_byte = pc.getc();
                /* Quick check to see if its postamble before adding to value */
                if (rx_byte == POSTAMBLE) {
                    // oop its done
                    rx_state = RX_TRANSMIT;
                    rx_buffPos = 0;
                    break;
                }
                update_val(rx_byte, rx_buffPos);
                rx_buffPos++;
                break;

            case RX_TRANSMIT:
                /* Transmit to the Crane Nucleo */
                bt_tx(BT_CRANE, PREAMBLE);
                bt_tx(BT_CRANE, buttons);
                bt_tx(BT_CRANE, l2);
                bt_tx(BT_CRANE, r2);
                bt_tx(BT_CRANE, lx);
                bt_tx(BT_CRANE, ly);
                bt_tx(BT_CRANE, rx);
                bt_tx(BT_CRANE, ry);
                bt_tx(BT_CRANE, POSTAMBLE);

                /* Transmit to the Train PCB */
                bt_tx(BT_TRAIN, PREAMBLE);
                bt_tx(BT_TRAIN, l2);
                bt_tx(BT_TRAIN, r2);
                bt_tx(BT_TRAIN, POSTAMBLE);

                // serial_print("--------------------\r\n");
                // serial_print("L2: %d\tR2: %d\r\n", l2, r2);
                // serial_print("LX: %d\tRX: %d\r\n", lx, rx);
                // serial_print("LY: %d\tRY: %d\r\n", ly, ry);
                // serial_print("--------------------\r\n");
                // serial_print("Buttons: %d\r\n", buttons);

                rx_state = RX_WAITING;
                break;

            default:
                serial_print("What the fuck how\r\n");
        }
    }
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Serial Thread - Process serial input
* @param  None
* @retval None
*/
void serial_thread( void ) {

    DigitalOut led(LED1);
    
    serial_print("Serial Thread Initialised\r\n");

    while(1) {

        if (rxFlag) {
            serial_clear_buffer();
        }
    }
}

/*----------------------------------------------------------------------------*/
