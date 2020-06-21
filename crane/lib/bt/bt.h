/** 
 **************************************************************
 * @file crane/lib/bt/bt.h
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void bt_tx( uint8_t tx_byte )
 *************************************************************** 
 */

#ifndef __BT_H
#define __BT_H

#include "../include/Pinduino.h"

/* Function prototypes -------------------------------------------------------*/
void bt_tx( uint8_t tx_byte );

#endif // __BT_H