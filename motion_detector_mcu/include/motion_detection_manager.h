/*
 * motion_detection_manager.h
 *
 *  Created on: 21 avr. 2014
 *      Author: essoussi
 */

#ifndef MOTION_DETECTION_MANAGER_H_
#define MOTION_DETECTION_MANAGER_H_


#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"

/* Public function prototypes -----------------------------------------------*/
extern void MDM_Se_UART1Init(void);
extern void MDM_Se_UART1Put(uint8_t data);
extern uint8_t MDM_Se_UART1Get();
extern void MDM_Se_UART2Init(void);
extern void MDM_Se_UART2Put(uint8_t data);
extern uint8_t MDM_Se_UART2Get();
/* --------------------------------------------------------------------------*/




#endif /* MOTION_DETECTION_MANAGER_H_ */
