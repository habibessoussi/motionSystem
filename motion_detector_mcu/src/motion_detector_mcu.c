/*
 * motion_detector_mcu.c
 *
 *  Created on: 18 avr. 2014
 *      Author: essoussi
 */

#include "mcu_init.h"
#include "mcu_utils.h"
#include "motion_detection_manager.h"

/* Application entry point */
int main()
{
	uint8_t receivedData;

	/* Init the Microcontroller */
	MDI_Se_Init();

	/* Init the UART1 */
	MDM_Se_UART1Init();

	/* Init the UART2 */
	MDM_Se_UART2Init();

	/* --- Turn on then after 1 second off the Green and blue LED to tell I am successfully initialized */
	/* Enable the GPIOB Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/* Turn on lights */
	MDU_Me_GPIO_HIGH(GPIOB, GPIO_Pin_7);
	MDU_Me_GPIO_HIGH(GPIOB, GPIO_Pin_6);

	/* Wait 1000 ms seconds */
	MDU_Se_Delay(1000);

	/* Turn off lights ! ready to go */
	MDU_Me_GPIO_LOW(GPIOB, GPIO_Pin_7);
	MDU_Me_GPIO_LOW(GPIOB, GPIO_Pin_6);


	/* Infinity loop */
	while (1)
	{
		/* Receive the data from the motion detector plugged through UART1 */
		receivedData = MDM_Se_UART1Get();

		/* Turn on  blue led to tell I received motion detector */
		MDU_Me_GPIO_HIGH(GPIOB, GPIO_Pin_6);

		/* Send the data received from motion detector to Raspberry via UART2 */
		MDM_Se_UART2Put(receivedData);

		/* Wait 60 ms seconds before turn off the blue led*/
		MDU_Se_Delay(60);
		MDU_Me_GPIO_LOW(GPIOB, GPIO_Pin_6);

	}
}

