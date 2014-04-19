/*
 * motion_detector_mcu.c
 *
 *  Created on: 18 avr. 2014
 *      Author: essoussi
 */

#include "mcu_init.h"

int main()
{
	/* Init the Microcontroller */
	MDI_Init();

	/* Turn on the Green LED to tell I am successfully initialized */
	GPIO_HIGH(GPIOB, GPIO_Pin_7);

	/* Infinity loop */
	while(1)
	{
		/*@ TODO ADD HERE USER APPLICATION*/
	}
}
