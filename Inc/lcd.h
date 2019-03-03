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

extern SPI_HandleTypeDef hspi5;
extern LTDC_HandleTypeDef hltdc;

void LCD_SpiInit();
void LCD_ModuleInit();
void LCD_WriteCommand(uint8_t data);
void LCD_WriteData(uint8_t data);
void LCD_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawColor(uint16_t Color);

#endif /* LCD_H_ */
