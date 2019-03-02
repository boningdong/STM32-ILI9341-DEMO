/*
 * user.c
 *
 *  Created on: Feb 28, 2019
 *      Author: Boning
 */
#include "main.h"
#include "user.h"

void LED_Init() {

	__HAL_RCC_GPIOG_CLK_ENABLE();

	GPIO_InitTypeDef Gpio_InitStruct;
	Gpio_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	Gpio_InitStruct.Pin = LED_PIN_GREEN | LED_PIN_RED;
	Gpio_InitStruct.Pull = GPIO_NOPULL;
	Gpio_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(LED_PORT, &Gpio_InitStruct);
}



