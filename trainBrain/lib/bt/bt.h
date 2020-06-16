/** 
 **************************************************************
 * @file host/lib/bt/bt.h
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Bluetooth Task header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */

#ifndef __BT_H
#define __BT_H

#define BUFFER_SIZE     80

/* Function prototypes -------------------------------------------------------*/
void bt_init( void );
void bt_tx( char *payload );
char *bt_read( void );
bool bt_rxFlag( void );
void bt_clear_buffer( void );

#endif // __CLI_H