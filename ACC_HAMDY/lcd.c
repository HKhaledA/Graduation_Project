/*
 * lcd.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */
#include <avr/io.h>
#include <stdlib.h>
#include "std_types.h"
#define FCPU 12000000
#include <util/delay.h>
#include "BIT_MATH.h"
#include"lcd.h"

void LCD_Init(void)
{
	_delay_ms(40);
	LCD_SendCommand (0b00111100);
	_delay_ms(3);
	LCD_SendCommand(0b00001100);
	_delay_ms(3);
	LCD_SendCommand (0b00000001);
	_delay_ms(3);
}

 void LCD_SendCommand(u8 command)
{
	CLRBIT (LCD_ControlPORT, EN_Pin);
	CLRBIT (LCD_ControlPORT, RW_Pin);
	CLRBIT (LCD_ControlPORT, RS_Pin);

	LCD_DataPORT= command;

	SETBIT (LCD_ControlPORT, EN_Pin);
	_delay_ms(2);
	CLRBIT (LCD_ControlPORT, EN_Pin);
}
 void LCD_Clear(void)
 {
	 LCD_SendCommand(0);
 }

 void LCD_WriteData(u8 data)
{
	CLRBIT (LCD_ControlPORT, EN_Pin);
	CLRBIT (LCD_ControlPORT, RW_Pin);
	SETBIT (LCD_ControlPORT, RS_Pin);

	LCD_DataPORT= data;

	SETBIT (LCD_ControlPORT, EN_Pin);
	_delay_ms(2);
	CLRBIT (LCD_ControlPORT, EN_Pin);
}

void LCD_DisplayString(u8* pu8StringCpy)
{

  /* Local loop index */
  u8 u8Index = 0;

  while (pu8StringCpy [u8Index] != 0)
  {
    /* Write Character on LCD */
    LCD_WriteData (pu8StringCpy [u8Index]);

    /* Increment local loop index */
    u8Index++;

    /* Delay to let the LCD show the character */
    _delay_ms(2);
  }

}

void LCD_Goto_xy(u8 x, u8 y)
{
	u8 firstcharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
	LCD_SendCommand (firstcharAdr[y-1] + x - 1);
	_delay_ms(1);
}

void LCD_MoveCursorLeft (void)
{
	LCD_SendCommand (LCD_MOVE_CURSOR_LEFT);
	_delay_ms(1);
}

//*******************************************************************************
void LCD_MoveCursorRight (void)
{
	LCD_SendCommand (LCD_MOVE_CURSOR_RIGHT);
	_delay_ms(1);
}

/*
void LCD_WriteString_xy(u8 x, u8 y, u8* pu8StringCpy)
{
	LCD_Goto_xy(x,y);
	LCD_WriteString(pu8StringCpy);
}

void LCD_WriteInteger_xy(u8 x, u8 y, u16 IntegerToDisplay, u8 NumberOfDigits)
{
	u8 StringToDisplay[NumberOfDigits];
	itoa (IntegerToDisplay, StringToDisplay, 10);
	LCD_WriteString_xy (x, y, StringToDisplay);
	LCD_WriteString(" ");  // 3lshan yms7 ay zeros btzhr (htfhm lma tgrb mn gherha)

}
*/
