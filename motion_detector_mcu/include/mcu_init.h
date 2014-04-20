/*
 * mcu_init.h
 *
 *  Created on: 19 avr. 2014
 *      Author: essoussi
 */

#ifndef MCU_INIT_H_
#define MCU_INIT_H_


#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"

/* Public function prototypes -----------------------------------------------*/
extern void MDI_Se_Init(void);
extern void MDI_Se_Delay(uint32_t nTime);
/* --------------------------------------------------------------------------*/

#endif /* MCU_INIT_H_ */
