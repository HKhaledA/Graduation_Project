/*
 * main.c
 *
 *  Created on: Jun 25, 2019
 *      Author: Abdur
 */


#include <avr/io.h>
#include <avr/iom128.h>
#include "std_types.h"
#include "BIT_MATH.h"
#define F_CPU 16000000UL
#include "util/delay.h"

int main (void)
{
	DDRA=0xff;
	DDRC=0xff;
	DDRD=0xff;
	DDRB=0xff;
	DDRE=0xff;
	DDRF=0xff;

	while(1)
	{
		_delay_ms(1000);
		PORTA=0xff;
		PORTC=0xff;
		PORTB=0xff;
		PORTD=0xff;
		PORTE=0xff;
		PORTF=0xff;
		_delay_ms(1000);
		PORTA=0;
		PORTC=0;
		PORTB=0;
		PORTF=0;
		PORTE=0;
		PORTD=0;
	}
	return 0;
}
