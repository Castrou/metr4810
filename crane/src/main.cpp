/** 
 **************************************************************
 * @file crane/src/main.cpp
 * @author Cameron Stroud - 44344968
 * @date idk what date but it isnt 20062020
 * @brief Crane Main (not Train) hehe rhymes
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */


/* Includes ***************************************************/
#include "mbed.h"

#include "Pinduino.h"

#include "serial.h"
#include "stepper.h"
#include "servo.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*----------------------------------------------------------------------------*/

/**
* @brief  Main
* @param  None
* @retval None
*/
int main()
{

    stepper_init();
    servo_init();
    myserial_init();
    
    /* Don't need while loop cause all functionality is run in an interrupt (yuck)
     * DISCLAIMER: Yes I hate myself for implementing it that way but it works
     * so I'm going with it
     */
    while(1);
}

/*----------------------------------------------------------------------------*/
