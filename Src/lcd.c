/*
 * lcd.c
 *
 *  Created on: Mar 1, 2019
 *      Author: Boning
 */

#include "main.h"
#include "lcd.h"


void LCD_SpiInit() {
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef gpioInit;
	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInit.Pin = LCD_PIN_NCS;
	gpioInit.Pull = GPIO_PULLUP;
	gpioInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(LCD_NCS_PORT, &gpioInit);
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(LCD_DCX_PORT, &gpioInit);

	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_SET);
}

void LCD_ModuleInit(SPI_HandleTypeDef *hspi) {
	HAL_GPIO_WritePin(LCD_IM0_GPIO_Port, LCD_IM0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_IM1_GPIO_Port, LCD_IM1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_IM2_GPIO_Port, LCD_IM2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_IM3_GPIO_Port, LCD_IM3_Pin, GPIO_PIN_RESET);

	LCD_WriteCommand(hspi, 0x01); // Software Reset
	LCD_WriteCommand(hspi, 0x11); // Exit Sleep
	//LCD_WriteCommand(hspi, 0x29); // Off Screen
	//LCD_WriteCommand(hspi, 0x28); // On Screen
}

void LCD_WriteCommand(SPI_HandleTypeDef *hspi, uint8_t data) {
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, &data, 1, 100);
	while(!((hspi->Instance->SR) & SPI_SR_TXE));
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
}

void LCD_ReadCommand(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t *rxdata, uint16_t size) {
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_RESET);
	// Send command
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	while(!((hspi->Instance->SR) & SPI_SR_TXE));
	HAL_SPI_Receive(hspi, rxdata, size, 100);
	while(!((hspi->Instance->SR) & SPI_SR_RXNE));
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
}

void LCD_WriteData(SPI_HandleTypeDef *hspi, uint8_t data) {
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_SET);
	HAL_SPI_Transmit(hspi, &data, 1, 100);
	while(!((hspi->Instance->SR) & SPI_SR_TXE));
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
}


