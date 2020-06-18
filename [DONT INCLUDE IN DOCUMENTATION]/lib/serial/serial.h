/** 
 **************************************************************
 * @file host/lib/serial/serial.cpp
 * @author Cameron Stroud - 44344968
 * @date 14062020
 * @brief Serial Task header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */

#ifndef __SERIAL_H
#define __SERIAL_H

/* Function prototypes -------------------------------------------------------*/
void myserial_init( void );
void serial_print(const char *payload, ...);

#endif // __SERIAL_H