/** 
 **************************************************************
 * @file crane/lib/stepper/stepper.cpp
 * @author Cameron Stroud - 44344968
 * @date 18062020
 * @brief Stepper header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void stepper_init( void );
 * void stepper_write( Stepper_t stepper, uint8_t axisVal );
 *************************************************************** 
 */

#ifndef __STEPPER_H
#define __STEPPER_H

/* Stepper Type */
typedef enum {
    STEPPER_ROTATE,
    STEPPER_HEIGHT,
    STEPPER_BOOM
} Stepper_t;

/* Function prototypes -------------------------------------------------------*/
void stepper_init();
void stepper_write(Stepper_t stepper, int8_t axisVal);

#endif // __SERIAL_H