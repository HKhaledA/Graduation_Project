#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "BIT_MATH.h"
/*#define F_CPU 8000000*/
#include "util/delay.h"
#include "lcd.h"

u8 adcResult [4];

int main (void)

{
	DDRD= 0xff;
	DDRB= 0xff;

	LCD_Init();

	/*------------------------- ADC Configuration ----------------------*/
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  // Prescaler 128
//	ADMUX  |= 1<<ADLAR;  // Left adjustment
	ADMUX |= 1<<REFS0;   // REF Voltage is VCC and no capacitor on AREF
	ADCSRA |= 1<<ADIE;	 // ADC interrupt enable
	ADCSRA |= 1<<ADEN;   // Enable ADC
	sei();				 // Enable global interrupt
	ADCSRA |= 1<<ADSC;
	/*------------------------------------------------------------------*/
	while(1)
	{
	}
	return 0;
}

ISR (ADC_vect)
{
	//u8 adcResult [4];

	u8 adc_low= ADCL;
	u16 adc_tenBits= ADCH<<8 | adc_low;

	itoa(adc_tenBits, adcResult, 10);
	LCD_Goto_xy(1,1);
	LCD_WriteString(adcResult);
	LCD_WriteString(" ");
	ADCSRA |= 1<<ADSC;  // Start the next conversion
}
