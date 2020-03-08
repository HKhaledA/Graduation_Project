/*
 * lcd.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef LCD_H_
#define LCD_H_


#define LCD_DataPORT		PORTB
#define LCD_ControlPORT		PORTC
#define EN_Pin				5
#define RW_Pin				6
#define RS_Pin				7

#define LCD_MOVE_CURSOR_LEFT     0x10                                           // move cursor left  (decrement)
#define LCD_MOVE_CURSOR_RIGHT    0x14                                           // move cursor right (increment)
#define LCD_MOVE_DISP_LEFT       0x18                                           // shift display left
#define LCD_MOVE_DISP_RIGHT      0x1C                                           // shift display right

#include "std_types.h"

void LCD_Init(void);
void LCD_SendCommand(u8 command);
void LCD_Clear(void);
void LCD_WriteData(u8 data);
void LCD_WriteString(u8* pu8StringCpy);
void LCD_Goto_xy(u8 x, u8 y);
void LCD_MoveCursorLeft (void);
void LCD_MoveCursorRight (void);
void LCD_WriteString_xy(u8 x, u8 y, u8* pu8StringCpy);
void LCD_WriteInteger_xy(u8 x, u8 y, u16 IntegerToDisplay, u8 NumberOfDigits);
void LCD_DisplayString(char * ptr)
void LCD_DisplayInt(s32 data);

#endif /* LCD_H_ */
