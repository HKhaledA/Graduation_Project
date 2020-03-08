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

/*------------------- Functions Prototypes --------------------*/
void Read_Flex(u16 adcDigial_Value);
/*-------------------------------------------------------------*/


u8 Volt;
u16 Digial_Value_0;
u16 Digial_Value_1;
u16 Digial_Value_2;
u16 Digial_Value_3;

int main (void)
{
	DDRC=0xff;
//	DDRA=0x00;

	ADC_init();

	while(1)
	{
		Digial_Value_0= ADC_GetResult(0);
		Read_Flex(Digial_Value_0);
		Digial_Value_1= ADC_GetResult(1);
		Read_Flex(Digial_Value_1);
		Digial_Value_2= ADC_GetResult(2);
		Read_Flex(Digial_Value_2);
		Digial_Value_3= ADC_GetResult(3);
		Read_Flex(Digial_Value_3);

		// El code da just bt2kd N el ADC channels sh8alen m3 b3d
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
