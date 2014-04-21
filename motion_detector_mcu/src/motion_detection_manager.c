/*
 * motion_detection_manager.c
 *
 *  Created on: 21 avr. 2014
 *      Author: essoussi
 */

#include "motion_detection_manager.h"

/* Private function prototypes -----------------------------------------------*/
static void MDM_Si_UARTxInit(USART_TypeDef * const UART);
static void MDM_Si_UARTxPut(uint8_t data, USART_TypeDef * const UART);
static uint8_t MDM_Si_UARTxGet(USART_TypeDef * const UART);
/* ---------------------------------------------------------------------------*/

/**
 * Initialize UART1
 */
void MDM_Se_UART1Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//enable USART2 clocks and GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* Connect P9 to USART1_Tx
	 * Connect P10 to USART1_Rx
	 * Connect P11 to USART1_CTS
	 * Connect P12 to USART1_RTS
	 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_USART1);

	//Set USART1 Tx (PA.09), as AF push-pull, Rx (PA.10)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 |
	GPIO_Pin_10 |
	GPIO_Pin_11 | GPIO_Pin_12;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	MDM_Si_UARTxInit(USART1);
}

/**
 * Put data in UART1
 * @param data data written in ports
 */
void MDM_Se_UART1Put(uint8_t data)
{
	MDM_Si_UARTxPut(data, USART1);
}

/**
 * Get the data from Rx pin
 * @return the data
 */
uint8_t MDM_Se_UART1Get()
{
	return MDM_Si_UARTxGet(USART1);
}

/**
 * Initialize UART2
 */
void MDM_Se_UART2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//enable USART2 clocks and GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* Connect P2 to USART2_Tx
	 * Connect P3 to USART2_Rx
	 * Connect P0 to USART2_CTS
	 * Connect P1 to USART2_RTS
	 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	//Set USART2 Tx (PA.02), as AF push-pull, Rx (PA.3)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |
	GPIO_Pin_1 |
	GPIO_Pin_2 | GPIO_Pin_3;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	MDM_Si_UARTxInit(USART2);
}

/**
 * Put data in UART2
 * @param data data written in ports
 */
void MDM_Se_UART2Put(uint8_t data)
{
	MDM_Si_UARTxPut(data, USART2);
}

uint8_t MDM_Se_UART2Get()
{
	return MDM_Si_UARTxGet(USART2);
}

void MDM_Si_UARTxPut(uint8_t data, USART_TypeDef * const UART)
{
	/* assert that the UART is either UART1 Or UART2 */
	assert_param(UART==USART1 || UART==USART2);

	USART_SendData(UART, (uint8_t) data);
	//Loop until the end of transmission
	while (USART_GetFlagStatus(UART, USART_FLAG_TC) == RESET)
	{
	}
}

uint8_t MDM_Si_UARTxGet(USART_TypeDef * const UART)
{

	/* assert that the UART is either UART1 Or UART2 */
	assert_param(UART==USART1 || UART==USART2);

	while (USART_GetFlagStatus(UART, USART_FLAG_RXNE) == RESET)
		;
	return (uint8_t) USART_ReceiveData(UART);
}

void MDM_Si_UARTxInit(USART_TypeDef * const UART)
{

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	/* assert that the UART is either UART1 Or UART2 */
	assert_param(UART==USART1 || UART==USART2);

	USART_ClockInit(UART, &USART_ClockInitStructure);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;

	//Write USART parameters
	USART_Init(UART, &USART_InitStructure);

	//Enable USART
	USART_Cmd(UART, ENABLE);
}
