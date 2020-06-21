/** 
 **************************************************************
 * @file trainBrain/lib/bt/bt.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void bt_init( void );
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>

#include "bt.h"
#include "motor.h"

/* Private typedef -----------------------------------------------------------*/

/* RX FSM States */
typedef enum {
    RX_WAITING,
    RX_RECEIVING,
    RX_EXECUTE
} RXState_t;

/* Controller Rx Packet Positions */
typedef enum {
    L2_VAL,
    R2_VAL
};

/* Private define ------------------------------------------------------------*/
#define PREAMBLE    0xFE
#define POSTAMBLE   0xFF

#define SIGN        0b10000000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RawSerial bt(PA_2, PA_3, 38400);

DigitalOut led1(PA_1);
DigitalOut led2(PA_0);

RXState_t btRx_state;
uint8_t btRx_val;
int btRx_buffPos = 0;

uint8_t l2 = 0;
uint8_t r2 = 0;

/* Private function prototypes -----------------------------------------------*/
void bt_rx_interrupt();

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Bluetooth Interrupt
* @param  None
* @retval None
*/
void bt_init( void ) {

    btRx_state = RX_WAITING;
    bt.attach(&bt_rx_interrupt, RawSerial::RxIrq);
    
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Update Controller input variables based on packet position
* @param  pos: Packet position
* @retval None
*/
void update_vals( int pos ) {

    switch(pos) {
        case L2_VAL:
            l2 = btRx_val;
            break;

        case R2_VAL:
            r2 = btRx_val;
            break;
    }
}

/*----------------------------------------------------------------------------*/

/**
* @brief  BT Interrupt for receive
* @param  None
* @retval None
*/
void bt_rx_interrupt( void ) {

    while (bt.readable()) {
        /* RX Finite State Machine */
        switch(btRx_state) {
            case RX_WAITING: // Waiting for packet
                btRx_val = bt.getc(); // Receive from buffer
                if (btRx_val == PREAMBLE) {
                    /* Start of packet received */
                    led1 = !led1;
                    btRx_state = RX_RECEIVING;
                }
                break;
            
            case RX_RECEIVING: // Receiving information
                btRx_val = bt.getc(); // Receive from buffer
                if (btRx_val == POSTAMBLE) {
                    /* End of packet received */
                    btRx_state = RX_EXECUTE;
                    break;
                }
                /* Update values based on packet position */
                update_vals(btRx_buffPos);
                btRx_buffPos++;
                break;
            
            case RX_EXECUTE:
                /* Write to motor */
                motor_write(l2, r2);

                /* Reset Rx variables */
                led2 = !led2;
                btRx_buffPos = 0;
                btRx_state = RX_WAITING;
                break;
        } 
    }
}

/*----------------------------------------------------------------------------*/
