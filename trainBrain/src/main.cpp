/** 
 **************************************************************
 * @file trainBrain/src/main.cpp
 * @author Cameron Stroud - 44344968
 * @date idk what date but it isnt 20062020
 * @brief Train Main (not Crane) hehe rhymes
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */


/* Includes ***************************************************/
#include <mbed.h>

#include "bt.h"
#include "motor.h"

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
int main() {

	/* Driver Initialisation */
	motor_init();
	bt_init();

	while(1); // See crane/src/main.cpp for explanation

}