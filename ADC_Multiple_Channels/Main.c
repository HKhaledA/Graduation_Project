/*
 * Main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */
#include<avr/io.h>
#include<util/delay.h>
#include "BIT_MATH.h"
#include"std_types.h"
#include"ADC.h"
#include"lcd.h"

int main(void)
{
	DDRD=DDRB=0xff;

	int Display_Volt, Display_Temp, Display_Light;
	int Volt,Temp,Light;
//	DDRA=0x00;
	ADC_init();
	LCD_Init();
	LCD_WriteString_xy(1, 1, "Volt= ");
	LCD_WriteString_xy(9, 1, "Temp= ");
	LCD_WriteString_xy(1, 2, "Light= ");
	while(1)
	{
		Volt=ADC_GetResult(0);
		Display_Volt=((5*Volt)/256);
		LCD_Goto_xy(7,1);
		LCD_WriteData(48+Display_Volt);
		//clr_bit(ADCSRA,6);
		_delay_ms(20);

		Temp=ADC_GetResult(1);
		Display_Temp=((50*Temp)/256);
		LCD_Goto_xy(13,1);
		LCD_WriteData(48+(Display_Temp/10));
		LCD_WriteData(48+(Display_Temp%10));

		//	clr_bit(ADCSRA,6);
		_delay_ms(20);

		Light=ADC_GetResult(2);
		Display_Light=((5*Light)/256);
		LCD_Goto_xy(8,2);
		if(Display_Light>=3)
		{
			LCD_WriteString("ON ");
		}
		if(Display_Light<3)
		{
			LCD_WriteString( "OFF");
		}
		//clr_bit(ADCSRA,6);
		_delay_ms(20);
	}
	return 0;
}

