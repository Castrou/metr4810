/** 
 **************************************************************
 * @file btModule_commandline/lib/bt/bt.h
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void bt_init( void );
 * void bt_tx( char *payload );
 *************************************************************** 
 */

#ifndef __BT_H
#define __BT_H

#include "../include/Pinduino.h"

#define BUFFER_SIZE     80

/* Global Typedef ------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
void bt_init( void );
void bt_tx( char *payload );

#endif // __BT_H