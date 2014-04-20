/*
 * mcu_utils.h
 *
 *  Created on: 20 avr. 2014
 *      Author: essoussi
 */

#ifndef MCU_UTILS_H_
#define MCU_UTILS_H_


#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"

/* Public function prototypes -----------------------------------------------*/
extern void MDU_Se_Delay(uint32_t nTime);
/* --------------------------------------------------------------------------*/


/* Public macros -----------------------------------------------*/
#define MDU_Me_GPIO_LOW(a,b)		a->BSRRH = b
#define MDU_Me_GPIO_HIGH(a,b)		a->BSRRL = b
/* ---------------------------------------------------------------------------*/


#endif /* MCU_INIT_H_ */
