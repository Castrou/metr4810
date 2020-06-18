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
#include "motor.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    RX_WAITING,
    RX_RECEIVING,
    RX_EXECUTE
} RXState_t;

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

const int buffer_size = BUFFER_SIZE;
char btRx_buffer[buffer_size+1];
RXState_t btRx_state;
uint8_t btRx_val;
int btRx_buffPos = 0;

int btRxFlag = 0;

uint8_t l2 = 0;
uint8_t r2 = 0;

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

    btRx_state = RX_WAITING;
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
* @brief  Update Controller input variables based on packet position
* @param  None
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
        btRx_val = bt.getc(); // Receive from buffer
        switch(btRx_state) {
            case RX_WAITING:
                if (btRx_val == 0xFE) {
                    led1 = !led1;
                    btRx_state = RX_RECEIVING;
                }
                break;
            
            case RX_RECEIVING:
                if (btRx_val == POSTAMBLE) {
                    btRx_state = RX_EXECUTE;
                    break;
                }
                update_vals(btRx_buffPos);
                btRx_buffPos++;
                break;
            
            case RX_EXECUTE:
                motor_write(l2, r2);
                led2 = !led2;
                btRx_buffPos = 0;
                btRx_state = RX_WAITING;
                break;
        } 
    }
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
uint8_t bt_read( void ) {
    
    return btRx_val;
}

/*----------------------------------------------------------------------------*/
