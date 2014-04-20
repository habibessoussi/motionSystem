/*
 * mcu_init.c
 *
 *  Created on: 19 avr. 2014
 *      Author: essoussi
 */

#include "mcu_init.h"
#include "mcu_utils.h"

/* Public function prototypes -----------------------------------------------*/
extern void MDI_Se_Init(void);
/* --------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void MDI_Si_RCC_Configuration(void);
static void MDI_Si_RTC_Configuration(void);
static void MDI_Si_Init_GPIOB(void);
/* ---------------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static RCC_ClocksTypeDef MDI_Ri_RCC_Clocks;
/* ---------------------------------------------------------------------------*/

void MDI_Se_Init(void) {
	/* Configure Clocks for Application need */
	MDI_Si_RCC_Configuration();

	/* Configure RTC Clocks */
	MDI_Si_RTC_Configuration();

	/* Set internal voltage regulator to 1.8V */
	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range1);

	/* Wait Until the Voltage Regulator is ready */
	while (PWR_GetFlagStatus(PWR_FLAG_VOS) != RESET)
		;

	/* Configure SysTick IRQ and SysTick Timer to generate interrupts every 500µs */
	RCC_GetClocksFreq(&MDI_Ri_RCC_Clocks);
	SysTick_Config(MDI_Ri_RCC_Clocks.HCLK_Frequency / 2000);
	/* Init I/O ports */
	MDI_Si_Init_GPIOB();

	/* Enable SysTick IRQ and SysTick Timer */
	SysTick->CTRL |= ( SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

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

	/* Disable the GPIOB Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, DISABLE);

}

/**
 * @brief  Configures the different system clocks.
 * @param  None
 * @retval None
 */
void MDI_Si_RCC_Configuration(void) {

	/* Enable HSI Clock */
	RCC_HSICmd(ENABLE);

	/*!< Wait till HSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET) {
	}

	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	RCC_MSIRangeConfig(RCC_MSIRange_6);

	RCC_HSEConfig(RCC_HSE_OFF);
	if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET) {
		while (1)
			;
	}

	/* Enable  comparator clock LCD and PWR mngt */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_LCD | RCC_APB1Periph_PWR, ENABLE);

	/* Enable ADC clock & SYSCFG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SYSCFG, ENABLE);

}

void MDI_Si_RTC_Configuration(void) {

	/* Allow access to the RTC */
	PWR_RTCAccessCmd(ENABLE);

	/* Reset Backup Domain */
	RCC_RTCResetCmd(ENABLE);
	RCC_RTCResetCmd(DISABLE);

	/* LSE Enable */
	RCC_LSEConfig(RCC_LSE_ON);

	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {
	}

	RCC_RTCCLKCmd(ENABLE);

	/* LCD Clock Source Selection */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

}

void MDI_Si_Init_GPIOB(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOB clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/* Configure the GPIO_LED pins  LD3 & LD4*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	MDU_Me_GPIO_LOW(GPIOB, GPIO_Pin_7);
	MDU_Me_GPIO_LOW(GPIOB, GPIO_Pin_6);

	/* Disable  GPIOB clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, DISABLE);

}
