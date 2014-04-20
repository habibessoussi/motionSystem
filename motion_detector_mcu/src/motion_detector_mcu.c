/*
 * motion_detector_mcu.c
 *
 *  Created on: 18 avr. 2014
 *      Author: essoussi
 */

#include "mcu_init.h"


/** Application entry point */
int main()
{
	/* Init the Microcontroller */
	MDI_Se_Init();

	/* Infinity loop */
	while(1)
	{
	}
}



