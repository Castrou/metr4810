/** 
 **************************************************************
 * @file crane/lib/serial/serial.cpp
 * @author Cameron Stroud - 44344968
 * @date 16062020
 * @brief Serial Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void myserial_init( void );
 * void serial_print(const char *payload, ...);
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>
#include <stdarg.h>
#include <stdio.h>

#include "serial.h"
#include "bt.h"
#include "stepper.h"
#include "servo.h"

/* Private typedef -----------------------------------------------------------*/

/* RX FSM States */
typedef enum {
    RX_WAITING,
    RX_RECEIVING,
    RX_TRANSMIT
} RxState_t;

/* Controller Rx Packet Order */
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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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

int rx_buffPos; // Position in packet
RxState_t rx_state; // Receiving state

DigitalOut led1(LED1);

/* Private function prototypes -----------------------------------------------*/
void serial_thread();
void serial_rx_interrupt();

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Serial Thread (serial_init conflicts with other function)
* @param  None
* @retval None
*/
void myserial_init( void ) {

    serial_print("Serial Interrupt Initialising...");
    rx_state = RX_WAITING;
    pc.attach(&serial_rx_interrupt, RawSerial::RxIrq);
    serial_print("Serial Interrupt Initialised\r\n");
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Send information to the console
* @param  payload: Message to send to console (same format as printf)
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
* @brief  Updates value based on packet position
* @param  value: value to be written
* @param  pos: position in packet
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

    uint8_t rx_byte;

    while(pc.readable()) {
        /* Rx Finite State Machine */
        switch(rx_state) {
            case RX_WAITING: // Waiting on packet
                rx_byte = pc.getc();
                if (rx_byte == PREAMBLE) {
                    /* Received the start of a packet */
                    rx_state = RX_RECEIVING;
                }
                break;

            case RX_RECEIVING: // Received preamble: packet building time
                rx_byte = pc.getc();

                /* Quick check to see if its postamble before adding to value */
                if (rx_byte == POSTAMBLE) {
                    /* End of packet received */
                    rx_state = RX_TRANSMIT;
                    rx_buffPos = 0;
                    break;
                }
                update_val(rx_byte, rx_buffPos);
                rx_buffPos++;
                break;

            case RX_TRANSMIT:

                // serial_print("--------------------\r\n");
                // serial_print("L2: %d\tR2: %d\r\n", l2, r2);
                // serial_print("LX: %d\tRX: %d\r\n", lx, rx);
                // serial_print("LY: %d\tRY: %d\r\n", ly, ry);
                // serial_print("--------------------\r\n");
                // serial_print("Buttons: %d\r\n", buttons);

                /* Steppers */
                stepper_write(STEPPER_ROTATE, rx);
                stepper_write(STEPPER_HEIGHT, ry);
                stepper_write(STEPPER_BOOM, ly);

                /* Rotating Servo */
                servoRotate_write(lx);

                /* Gripper Servos */
                if ((buttons & R1_BUTTON) == R1_BUTTON) {
                    led1 = !led1;
                    servoGrip_toggle();
                }

                /* Train Motor */
                bt_tx(PREAMBLE);
                bt_tx(l2);
                bt_tx(r2);
                bt_tx(POSTAMBLE);

                rx_state = RX_WAITING;
                break;

            default:
                serial_print("If you are reading this: something's fucked.\r\n");
        }
    }
}

/*----------------------------------------------------------------------------*/
