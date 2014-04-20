/*
 * mcu_utils.c
 *
 *  Created on: 20 avr. 2014
 *      Author: essoussi
 */

#include "mcu_utils.h"

/* Private function prototypes -----------------------------------------------*/
static void MDU_Si_TimingDelay_Decrement(void);
/* ---------------------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
static volatile uint32_t MDU_Ri_TimingDelay;
/* ---------------------------------------------------------------------------*/

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in ms.
 * @retval None
 */

void MDU_Se_Delay(uint32_t nTime) {
	MDU_Ri_TimingDelay = nTime;
	while (MDU_Ri_TimingDelay != 0)
		;
}

/**
 * @brief  Decrements the MDU_Ri_TimingDelay variable.
 * @param  None
 * @retval None
 */
void MDU_Si_TimingDelay_Decrement(void) {

	if (MDU_Ri_TimingDelay != 0x00) {
		MDU_Ri_TimingDelay--;
	}

}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
	MDU_Si_TimingDelay_Decrement();
}
