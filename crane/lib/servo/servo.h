/** 
 **************************************************************
 * @file crane/lib/servo/servo.h
 * @author Cameron Stroud - 44344968
 * @date 20062020
 * @brief Servo header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void servo_init()
 * void servoRotate_write( uint8_t axisVal )
 * void servoGrip_toggle()
 *************************************************************** 
 */

#ifndef __SERVO_H
#define __SERVO_H

/* Function prototypes -------------------------------------------------------*/
void servo_init( void );
void servoRotate_write( uint8_t axisVal );
void servoGrip_toggle( void );

#endif // __SERVO_H