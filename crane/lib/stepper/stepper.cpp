/** 
 **************************************************************
 * @file crane/lib/stepper/stepper.cpp
 * @author Cameron Stroud - 44344968
 * @date 18062020
 * @brief Stepper source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void stepper_init( void );
 * void stepper_write( Stepper_t stepper, uint8_t axisVal );
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>


#include "stepper.h"
#include "serial.h"
#include "../include/Pinduino.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BYTE_LEN        7

#define SIGN_MASK       0b10000000
#define VAL_MASK        0b01111111

#define STEPPER_CNT     3

#define ROTATE_PIN      D3_PIN
#define HEIGHT_PIN      D5_PIN
#define BOOM_PIN        D9_PIN

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PwmOut StepperRotateSpeed(D3_PIN);
PwmOut StepperHeightSpeed(D5_PIN);
PwmOut StepperBoomSpeed(D9_PIN);

DigitalOut StepperRotateDir(D4_PIN);
DigitalOut StepperHeightDir(D6_PIN);
DigitalOut StepperBoomDir(D7_PIN);

/* Private function prototypes -----------------------------------------------*/

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Steppers
* @param  None
* @retval None
*/
void stepper_init( void ) {

    StepperRotateSpeed.period_ms(5);
    StepperRotateSpeed.write(0);
    StepperRotateDir = 0;

    StepperHeightSpeed.period_ms(5);
    StepperHeightSpeed.write(0);
    StepperHeightDir = 0;

    StepperBoomSpeed.period_ms(5);
    StepperBoomSpeed.write(0);
    StepperBoomDir = 0;

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Maps axis value to duty cycle
* @param  axisVal: Controller joystick axis value (-100 <= x <= 100)
* @retval None
*/
float stepper_mapSpeed( int8_t axisVal ) {

    float dutyCycle = 0;

    /* Max stepper speed is 50% duty cycle (cause each rising is step)
     * Map values 0-100 to 0-0.5
     */
    dutyCycle = (float)(((axisVal & VAL_MASK) / 2) / 100.0);

    return dutyCycle;

}

/*----------------------------------------------------------------------------*/

/**
* @brief  Writes to stepper based on axis value
* @param  stepper: Stepper to write to
* @param  axisVal: Controller joystick axis value
* @retval None
*/
void stepper_write( Stepper_t stepper, int8_t axisVal ) {

    float dutyCycle = stepper_mapSpeed(axisVal);

    switch(stepper) {
        case STEPPER_ROTATE:
            StepperRotateDir = (axisVal & SIGN_MASK);
            StepperRotateSpeed.write(dutyCycle);
            break;
        
        case STEPPER_HEIGHT:
            StepperHeightDir = (axisVal & SIGN_MASK);
            StepperHeightSpeed.write(dutyCycle);
            break;

        case STEPPER_BOOM:
            StepperBoomDir = (axisVal & SIGN_MASK);
            StepperBoomSpeed.write(dutyCycle);
            break;
    }    
}

/*----------------------------------------------------------------------------*/