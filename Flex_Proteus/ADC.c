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
	ADMUX|=(1<<REFS0)|(1<<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

u16 ADC_GetResult(u8 channel)
{
	u16 value;
	ADMUX|= (channel&(0b00000111));
	ADCSRA|= (1<<ADSC);
	while((ADCSRA & (1<<ADSC))!=0);
	value=ADCH;
	ADCSRA|= 0x10;
	return value;
}
