/** 
 **************************************************************
 * @file crane/lib/servo/servo.cpp
 * @author Cameron Stroud - 44344968
 * @date 20062020
 * @brief Stepper source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void servo_init()
 * void servoRotate_write( uint8_t axisVal )
 * void servoGrip_toggle()
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>


#include "servo.h"
#include "serial.h"
#include "../include/Pinduino.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BYTE_LEN        7

#define SIGN_MASK       0b10000000
#define VAL_MASK        0b01111111

#define GRIP_ON         0.0019f
#define GRIP_OFF        0.0011f

#define SERVO_MAX       0.0019f
#define SERVO_MIN       0.0011f
#define SERVO_IDLE      0.0015f

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PwmOut servoRotate(D10_PIN);
PwmOut servoGrip(D11_PIN);

float servoRotatePulse;
float servoGripStatus = GRIP_OFF;

/* Private function prototypes -----------------------------------------------*/
float servo_mapPulse(int angle);

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Servos
* @param  None
* @retval None
*/
void servo_init( void ) {

    servoRotate.period_ms(20);
    servoGrip.period_ms(20);

    servoRotatePulse = SERVO_IDLE;
    servoRotate.pulsewidth(servoRotatePulse);

    servoGrip.pulsewidth(GRIP_OFF);

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Maps axis value to angle increment
* @param  axisVal: Controller joystick axis value (-100 <= x <= 100)
* @retval Change in angle
*/
float servo_mapSpeed( uint8_t axisVal ) {

    int8_t angle;
    int sign = 1 - (2*((axisVal & SIGN_MASK) >> BYTE_LEN));
    /* Full angle increment is 10 degrees
     * Map 0-100 to 0-10
     */
    angle = sign * ((VAL_MASK & axisVal) / 10);

    return angle;

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Maps angle to Pulsewidth
* @param  angle: Change in angle desired
* @retval Pulsewidth in seconds
*/
float servo_mapPulse( int angle ) {

    float pulse = SERVO_IDLE;

    /* 0 deg - 180 deg
     * 1 ms pulse for 0; 2 ms pulse for 180
     * divide by 180 + 1
     */
    pulse += (((float) angle / 180.0) / 1000.0);

    return pulse;

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Writes to servo based on axis value
* @param  None
* @retval None
*/
void servoRotate_write( uint8_t axisVal ) {

    /* Get angle increment of given axis value */
    int angleIncrement = servo_mapSpeed(axisVal);
    /* Calculate new pulsewidth */
    servoRotatePulse = servo_mapPulse(angleIncrement);

    /* Limit check */
    // if (servoRotatePulse >=  SERVO_MAX) {
    //     servoRotatePulse = SERVO_MAX;
    // } else if (servoRotatePulse <= SERVO_MIN) {
    //     servoRotatePulse = SERVO_MIN;
    // }

    /* Write value */
    servoRotate.pulsewidth(servoRotatePulse);
    
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Toggles Gripper position
* @param  None
* @retval None
*/
void servoGrip_toggle( void ) {

    if (servoGripStatus == GRIP_OFF) {
        servoGripStatus = GRIP_ON;
        servoGrip.pulsewidth(servoGripStatus);
    } else {
        servoGripStatus = GRIP_OFF;
        servoGrip.pulsewidth(servoGripStatus);
    }
}