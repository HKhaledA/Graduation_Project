#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "BIT_MATH.h"
/*#define F_CPU 8000000*/
#include "util/delay.h"
#include "lcd.h"

u8 adc_Result [4];

int main (void)

{
	DDRD= 0xff;
	DDRB= 0xff;

	LCD_Init();
	LCD_Goto_xy(1,1);
	LCD_WriteString("F1= ");
	LCD_Goto_xy(1,2);
	LCD_WriteString("F2= ");
	LCD_Goto_xy(9,1);
	LCD_WriteString("F3= ");
	LCD_Goto_xy(9,2);
	LCD_WriteString("F4= ");

	/*------------------------- ADC Configuration ----------------------*/
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  // Prescaler 128
	//ADMUX  |= 1<<ADLAR;  // Left adjustment
	ADMUX |= (1<<REFS1) | (1<<REFS0);   // REF Voltage is 2.56 with capacitor on AREF pin
	// ADMUX= 0b11000000
	ADCSRA |= 1<<ADIE;	 // ADC interrupt enable
	ADCSRA |= 1<<ADEN;   // Enable ADC
	sei();				 // Enable global interrupt
	ADCSRA |= 1<<ADSC;
	/*------------------------------------------------------------------*/

	while(1)
	{}

	return 0;
}


ISR (ADC_vect)
{
	u8 adc_low= ADCL;
	u16 adc_tenBitValue= ADCH <<8 | adc_low;

	switch (ADMUX)
	{
		case 0xc0:  // ADMUX= 0b11000000 ---> 0xC0
			itoa(adc_tenBitValue, adc_Result, 10);
			LCD_Goto_xy(4,1);
			LCD_WriteString(adc_Result);
			LCD_WriteString(" "); //3lshan yms7 ay digits tb3 elrkm el2deem lsa zahra 3 el LCD (htfhmha lma tgrb tms7ha :D )
			ADMUX= 0xc1;   // To be switched to Channel 1
			break;
		case 0xc1:  // ADMUX= 0b11000001 ---> 0xC1
			itoa(adc_tenBitValue, adc_Result, 10);
			LCD_Goto_xy(4,2);
			LCD_WriteString(adc_Result);
			LCD_WriteString(" ");
			ADMUX= 0xc2;	// To be switched to Channel 0
			break;
		case 0xc2:  // ADMUX= 0b11000000 ---> 0xC0
			itoa(adc_tenBitValue, adc_Result, 10);
			LCD_Goto_xy(12,1);
			LCD_WriteString(adc_Result);
			LCD_WriteString(" ");
			ADMUX= 0xc3;   // To be switched to Channel 1
			break;
		case 0xc3:  // ADMUX= 0b11000001 ---> 0xC1
			itoa(adc_tenBitValue, adc_Result, 10);
			LCD_Goto_xy(12,2);
			LCD_WriteString(adc_Result);
			LCD_WriteString(" ");
			ADMUX= 0xc0;	// To be switched to Channel 0
	}
	ADCSRA |= 1<<ADSC;  // Start the next conversion
}
