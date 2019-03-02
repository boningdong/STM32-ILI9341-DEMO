/*
 * lcd.h
 *
 *  Created on: Mar 1, 2019
 *      Author: Boning
 */

#include "main.h"

#ifndef LCD_H_
#define LCD_H_

#define LCD_NCS_PORT GPIOC
#define LCD_DCX_PORT GPIOD

#define LCD_PIN_NCS GPIO_PIN_2
#define LCD_PIN_DCX GPIO_PIN_13

void LCD_SpiInit();
void LCD_ModuleInit(SPI_HandleTypeDef *hspi);
void LCD_WriteCommand(SPI_HandleTypeDef *hspi, uint8_t data);
void LCD_WriteData(SPI_HandleTypeDef *hspi, uint8_t data);

void LCD_ReadCommand(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t *rxdata, uint16_t size);

#endif /* LCD_H_ */
