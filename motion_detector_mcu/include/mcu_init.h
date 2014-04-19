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
extern void MDI_Init(void);
/* ---------------------------------------------------------------------------*/

/* Public macros -----------------------------------------------*/
#define GPIO_LOW(a,b)		a->BSRRH = b
#define GPIO_HIGH(a,b)		a->BSRRL = b
/* ---------------------------------------------------------------------------*/

#endif /* MCU_INIT_H_ */
