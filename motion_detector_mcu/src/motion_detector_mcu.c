/*
 * motion_detector_mcu.c
 *
 *  Created on: 18 avr. 2014
 *      Author: essoussi
 */

#include "mcu_init.h"


/* Public function prototypes -----------------------------------------------*/
static inline void MDM_Si_Delay(uint32_t nTime);
/* ---------------------------------------------------------------------------*/


/** Application entry point */
int main()
{
	/* Init the Microcontroller */
	MDI_Se_Init();

	/* --- Turn off then after 1 second on the Green and blue LED to tell I am successfully initialized */

	/* Enable the GPIOB Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	MDI_Me_GPIO_HIGH(GPIOB, GPIO_Pin_7);
	MDI_Me_GPIO_HIGH(GPIOB, GPIO_Pin_6);

	/* Wait 1000 ms seconds */
	MDI_Se_Delay(1000);

	MDI_Me_GPIO_LOW(GPIOB, GPIO_Pin_7);
	MDI_Me_GPIO_LOW(GPIOB, GPIO_Pin_6);

	/* Disable the GPIOB Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, DISABLE);

	/* Infinity loop */
	while(1)
	{
	}
}



