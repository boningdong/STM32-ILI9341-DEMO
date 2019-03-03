/*
 * lcd.h
 *
 *  Created on: Mar 1, 2019
 *      Author: Boning
 */

#include "main.h"


#ifndef LCD_H_
#define LCD_H_

#define LCD_WIDTH 20
#define LCD_HEIGHT 20

// LCD Interface
#define LCD_DCX_PORT GPIOD
#define LCD_PIN_DCX GPIO_PIN_13

// SPI Interface
#define LCD_NCS_PORT GPIOC
#define LCD_PIN_NCS GPIO_PIN_2
extern SPI_HandleTypeDef hspi5;

void LCD_WriteCommand(uint8_t data);
void LCD_WriteData(uint8_t data);
void LCD_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawColor(uint16_t Color);
void LCD_SPI_DrawRect(uint16_t x0 , uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

// LTDC Interface
#define LCD_WRX_PORT GPIOD
#define LCD_RDX_PORT GPIOD
#define LCD_TE_PORT GPIOD
#define LCD_PIN_WRX GPIO_PIN_13
#define LCD_PIN_RDX GPIO_PIN_12
#define LCD_PIN_TE GPIO_PIN_11
extern LTDC_HandleTypeDef hltdc;

void LCD_SpiInit();
void LCD_LtdcInit();
void LCD_ModuleInit();

void LCD_LTDC_DrawRect(uint16_t x0 , uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);


#endif /* LCD_H_ */
