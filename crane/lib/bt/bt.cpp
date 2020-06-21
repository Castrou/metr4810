/** 
 **************************************************************
 * @file crane/lib/bt/bt.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void bt_tx( uint8_t tx_byte )
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>

#include "bt.h"
#include "serial.h"
#include "stepper.h"
#include "servo.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RawSerial bt(D8_PIN, D2_PIN, 38400);

/* Private function prototypes -----------------------------------------------*/

/*----------------------------------------------------------------------------*/

/**
* @brief  BT Thread - Process bluetooth RX info
* @param  tx_byte: Byte to transmit over bluetooth
* @retval None
*/
void bt_tx( uint8_t tx_byte ) {

    bt.putc(tx_byte);
}


/*----------------------------------------------------------------------------*/
