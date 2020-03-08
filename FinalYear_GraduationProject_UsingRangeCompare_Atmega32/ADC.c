/*
 * ADC.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */
#include<avr/io.h>
#include"std_types.h"
#include "ADC.h"

void ADC_init(void)
{
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
//	ADMUX|=(1<<REFS0)|(1<<REFS1)|(1<<ADLAR);
	ADMUX|=(1<<REFS0)|(1<<ADLAR);
}

int ADC_GetResult(u8 channel)
{
	int value;
	ADMUX &= 0b01111000;
	ADMUX |= (channel & (0b00000111) );
	ADCSRA|= (1<<ADSC);
	while((ADCSRA & (1<<ADSC))!=0);
	value=ADCH;
	ADCSRA|= 0x10;
	return value;
}
