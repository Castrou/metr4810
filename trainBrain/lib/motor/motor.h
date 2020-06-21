/** 
 **************************************************************
 * @file host/lib/motor/motor.h
 * @author Cameron Stroud - 44344968
 * @date 17062020
 * @brief Motor header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void motor_init( void );
 * void motor_write( uint8_t l2val, uint8_t r2val );
 *************************************************************** 
 */

#ifndef __MOTOR_H
#define __MOTOR_H

/* Function prototypes -------------------------------------------------------*/
void motor_init( void );
void motor_write( uint8_t l2val, uint8_t r2val );

#endif // __MOTOR_H