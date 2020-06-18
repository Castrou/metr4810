/** 
 **************************************************************
 * @file trainBrain/lib/motor/motor.cpp
 * @author Cameron Stroud - 44344968
 * @date 17062020
 * @brief Motor source file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BYTE_LEN    7

#define SIGN_MASK   0b10000000
#define VALUE_MASK  0b01111111

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PwmOut forwardSpeed(PA_9);
PwmOut reverseSpeed(PA_10);
/* Private function prototypes -----------------------------------------------*/

/*----------------------------------------------------------------------------*/

/**
* @brief  Initialises Motors
* @param  None
* @retval None
*/
void motor_init( void ) {

    forwardSpeed.period_ms(20);
    reverseSpeed.period_ms(20);

    forwardSpeed.write(0);
    reverseSpeed.write(0);
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Maps Trigger Values to a Duty cycle
* @param  None
* @retval None
*/
float motor_mapSpeed( uint8_t triggerVal ) {

    float dutyCycle = 0.25f;
    int sign = 1 - (2*(triggerVal & SIGN_MASK >> BYTE_LEN)); // Sign stored at big end

    /* Trigger val ranges from 0 - 100 (without sign)
     * Half it to get 0-25 (capped at max 50 cause of 3v motor)
     * Add to duty cycle (or take depending on sign) to get % val as decimal
     */
    dutyCycle += (sign * ((triggerVal & VALUE_MASK) / 4)) / 100.0;

    return dutyCycle;
    
}

/*----------------------------------------------------------------------------*/

/**
* @brief  Write speed to motor
* @param  None
* @retval None
*/
void motor_write( uint8_t l2Val, uint8_t r2Val ) {

    float l2Speed = motor_mapSpeed(l2Val);
    float r2Speed = motor_mapSpeed(r2Val);

    forwardSpeed.write(r2Speed);
    reverseSpeed.write(l2Speed);

}