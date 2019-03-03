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
	gpioInit.Pin = LCD_PIN_DCX;
	HAL_GPIO_Init(LCD_DCX_PORT, &gpioInit);

	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_SET);
}

void LCD_ModuleInit() {
	HAL_GPIO_WritePin(LCD_IM0_GPIO_Port, LCD_IM0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_IM1_GPIO_Port, LCD_IM1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_IM2_GPIO_Port, LCD_IM2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_IM3_GPIO_Port, LCD_IM3_Pin, GPIO_PIN_RESET);

	//SOFTWARE RESET
	LCD_WriteCommand(0x01);
	HAL_Delay(1000);

	//POWER CONTROL A
	LCD_WriteCommand(0xCB);
	LCD_WriteData(0x39);
	LCD_WriteData(0x2C);
	LCD_WriteData(0x00);
	LCD_WriteData(0x34);
	LCD_WriteData(0x02);

	//POWER CONTROL B
	LCD_WriteCommand(0xCF);
	LCD_WriteData(0x00);
	LCD_WriteData(0xC1);
	LCD_WriteData(0x30);


	//DRIVER TIMING CONTROL A
	LCD_WriteCommand(0xE8);
	LCD_WriteData(0x85);
	LCD_WriteData(0x00);
	LCD_WriteData(0x78);

	//DRIVER TIMING CONTROL B
	LCD_WriteCommand(0xEA);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);

	//POWER ON SEQUENCE CONTROL
	LCD_WriteCommand(0xED);
	LCD_WriteData(0x64);
	LCD_WriteData(0x03);
	LCD_WriteData(0x12);
	LCD_WriteData(0x81);

	//PUMP RATIO CONTROL
	LCD_WriteCommand(0xF7);
	LCD_WriteData(0x20);

	//POWER CONTROL,VRH[5:0]
	LCD_WriteCommand(0xC0);
	LCD_WriteData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	LCD_WriteCommand(0xC1);
	LCD_WriteData(0x10);

	//VCM CONTROL
	LCD_WriteCommand(0xC5);
	LCD_WriteData(0x3E);
	LCD_WriteData(0x28);

	//VCM CONTROL 2
	LCD_WriteCommand(0xC7);
	LCD_WriteData(0x86);

	/*
	//MEMORY ACCESS CONTROL
	LCD_WriteCommand(0x36);
	LCD_WriteData(0x48);*/

	//PIXEL FORMAT
	LCD_WriteCommand(0x3A);
	LCD_WriteData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	LCD_WriteCommand(0xB1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x18);

	//DISPLAY FUNCTION CONTROL
	LCD_WriteCommand(0xB6);
	LCD_WriteData(0x08);
	LCD_WriteData(0x82);
	LCD_WriteData(0x27);


	//3GAMMA FUNCTION DISABLE
	LCD_WriteCommand(0xF2);
	LCD_WriteData(0x00);

	//GAMMA CURVE SELECTED
	LCD_WriteCommand(0x26);
	LCD_WriteData(0x01);

	//POSITIVE GAMMA CORRECTION
	LCD_WriteCommand(0xE0);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x31);
	LCD_WriteData(0x2B);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x08);
	LCD_WriteData(0x4E);
	LCD_WriteData(0xF1);
	LCD_WriteData(0x37);
	LCD_WriteData(0x07);
	LCD_WriteData(0x10);
	LCD_WriteData(0x03);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x09);
	LCD_WriteData(0x00);

	//NEGATIVE GAMMA CORRECTION
	LCD_WriteCommand(0xE1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x14);
	LCD_WriteData(0x03);
	LCD_WriteData(0x11);
	LCD_WriteData(0x07);
	LCD_WriteData(0x31);
	LCD_WriteData(0xC1);
	LCD_WriteData(0x48);
	LCD_WriteData(0x08);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x31);
	LCD_WriteData(0x36);
	LCD_WriteData(0x0F);

	//EXIT SLEEP
	LCD_WriteCommand(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	LCD_WriteCommand(0x29);
}

// Basic Communication Functions
void LCD_WriteCommand(uint8_t data) {
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, &data, 1, 10);
	while(!((hspi5.Instance->SR) & SPI_SR_TXE));
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
}

void LCD_WriteData(uint8_t data) {
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi5, &data, 1, 10);
	while(!((hspi5.Instance->SR) & SPI_SR_TXE));
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
}

// Advanced Functions
void LCD_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	LCD_WriteCommand( 0x2A);
	LCD_WriteData( (x1 >> 8) & 0xFF);
	LCD_WriteData( x1 & 0xFF);
	LCD_WriteData((x2 >> 8) & 0xFF);
	LCD_WriteData(x2 & 0xFF);

	LCD_WriteCommand( 0x2B);
	LCD_WriteData((y1 >> 8) & 0xFF);
	LCD_WriteData(y1 & 0xFF);
	LCD_WriteData((y2 >> 8) & 0xFF);
	LCD_WriteData(y2 & 0xFF);

	LCD_WriteCommand( 0x2c);
}

void LCD_DrawColor(uint16_t Color)
{
	unsigned char TempBuffer[2] = {Color>>8, Color};
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_PIN_DCX, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi5, TempBuffer, 2, 1);
	HAL_GPIO_WritePin(LCD_NCS_PORT, LCD_PIN_NCS, GPIO_PIN_SET);
}


