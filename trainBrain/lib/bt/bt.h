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
void bt_read( char **payload );
bool bt_rxFlag( void );
void bt_clearFlag(void);

#endif // __CLI_H