/*
 * lcd.h
 *
 *  Created on: ??�/??�/????
 *      Author: DELL
 */

#ifndef LCD_H_
#define LCD_H_


#define LCD_DataPORT		PORTD
#define LCD_ControlPORT		PORTB
#define EN_Pin				0
#define RW_Pin				1
#define RS_Pin				2

#define LCD_MOVE_CURSOR_LEFT     0x10                                           // move cursor left  (decrement)
#define LCD_MOVE_CURSOR_RIGHT    0x14                                           // move cursor right (increment)
#define LCD_MOVE_DISP_LEFT       0x18                                           // shift display left
#define LCD_MOVE_DISP_RIGHT      0x1C                                           // shift display right


void LCD_Init(void);
void LCD_SendCommand(u8 command);
void LCD_WriteData(u8 data);
void LCD_WriteString(u8* pu8StringCpy);
void LCD_Goto_xy(u8 x, u8 y);
void LCD_MoveCursorLeft (void);
void LCD_MoveCursorRight (void);


#endif /* LCD_H_ */
