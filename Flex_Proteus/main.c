/*
 * main.c
 *
 */


#include <avr/io.h>
#include "std_types.h"
#include "BIT_MATH.h"
/*#define F_CPU 8000000*/
#include "util/delay.h"
#include "lcd.h"
#include "ADC.h"

u8 Volt;
u16 Digial_Value;
int main (void)
{
	DDRB=0xff;
	DDRC=0xff;
	DDRA=0x00;
	u8 _1st_Digit;
	u8 _2nd_Digit;
	u8 _3rd_Digit;
	LCD_Init();
	LCD_Goto_xy(1,1);
	LCD_WriteString("Volt= ");
	LCD_Goto_xy(1,2);
	LCD_WriteString("Dig. Value= ");
	ADC_init();
	while(1)
	{
		Digial_Value= ADC_GetResult(0);
		Volt=(5*Digial_Value)/255;
		_1st_Digit= Digial_Value/100 + 48 ;
		_2nd_Digit= ((Digial_Value % 100) / 10) + 48 ;
		_3rd_Digit= ((Digial_Value % 100) % 10) + 48 ;
		LCD_Goto_xy(7,1);
		LCD_WriteData(Volt+48);
		LCD_Goto_xy(12,2);
		LCD_WriteData( _1st_Digit);
		LCD_Goto_xy(13,2);
		LCD_WriteData( _2nd_Digit);
		LCD_Goto_xy(14,2);
		LCD_WriteData( _3rd_Digit);
	}
	return 0;
}
