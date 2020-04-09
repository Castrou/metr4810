/** 
**************************************************************
* @file crane/src/main.cpp
* @author Cameron Stroud - 44344968
* @date 07042020
* @brief Crane application file
***************************************************************
*/

/* Includes ***************************************************/
#include <Arduino.h>

#include "STM32FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Example_PRIORITY (tskIDLE_PRIORITY + 2)
#define Example_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TaskHandle_t ExampleHandler;

/* Private function prototypes -----------------------------------------------*/
void Example_Task(void *pvParameter);


void setup() {
	/* Initialisation Functions */
	/* Application Task Creation */ // won't exist ordinarily
    xTaskCreate(
					Example_Task, 			/* Task function */
					"Example Task", 		/* Task Name */
					Example_STACK_SIZE,		/* Stack Size */
					NULL, 					/* Parameters or some shit idk i dont use it */
					Example_PRIORITY, 		/* Priority */
					NULL);					/* Task Handler */

	/* Start the Task Scheduler */
	vTaskStartScheduler(); // Shouldn't get past this point - only would if there's not enough RAM
}

void loop() {
	/* Don't need it cause everything is done through tasks */
}

void Example_Task(void *pvParameters) {

	/* Setup LED as output */
	pinMode(13, OUTPUT);

	for (;;) {
		digitalWrite(13, !digitalRead(13));
		vTaskDelay(1000);
	}

}