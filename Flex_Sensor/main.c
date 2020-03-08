/*
 * main.c
 *
 */


#include <avr/io.h>
#include "std_types.h"
#include "BIT_MATH.h"
#define F_CPU 12000000
#include "util/delay.h"
#include "lcd.h"
#include "ADC.h"

#define Flex_Offset	85

/*------------------- Functions Prototypes --------------------*/
void Read_Flex(u16 adcDigial_Value);
/*-------------------------------------------------------------*/


u8 Volt;
u16 Digial_Value;
u8 Flex;
int main (void)
{
	DDRD=0xff;
	DDRB=0xff;
	DDRC= 0xff;
//	DDRA=0x00;

	LCD_Init();
	LCD_WriteString_xy(1, 1, "Volt=");
	LCD_Goto_xy(1,2);
	LCD_WriteString_xy(1, 2, "Dig. Value= ");
	ADC_init();
	while(1)
	{
		Digial_Value= ADC_GetResult(0);
		Volt=(5*Digial_Value)/ (u8)255;

		if (Digial_Value - Flex_Offset > 60)
			Flex=0;
		else if ( (Digial_Value - Flex_Offset <= 60) && (Digial_Value - Flex_Offset > 30) )
			Flex=1;
		else if ( (Digial_Value - Flex_Offset <= 30) && (Digial_Value - Flex_Offset > 20) )
			Flex=2;
		else if ( (Digial_Value - Flex_Offset <= 20) && (Digial_Value - Flex_Offset > 5) )
			Flex=3;
		else if (Digial_Value - Flex_Offset < 5)
			Flex=4;

		/*-------- Displaying The output on LCD ---------*/
		LCD_WriteInteger_xy(7, 1, Volt, 4);
		LCD_WriteInteger_xy(12, 2, Flex, 4);
		/*-----------------------------------------------*/

//		Read_Flex(Digial_Value);
	}
	return 0;
}

void Read_Flex(u16 adcDigial_Value)
{
	if ( (adcDigial_Value > 0) && (adcDigial_Value <= 15) )
		PORTC= 0x01;
	else if ( (adcDigial_Value > 15) && (adcDigial_Value <= 30) )
		PORTC= 0x02;
	else if ( (adcDigial_Value > 30) && (adcDigial_Value <= 45) )
		PORTC= 0x04;
	else if ( (adcDigial_Value > 45) && (adcDigial_Value <= 60) )
		PORTC= 0x08;
	else
		PORTC= 0x00;
}
