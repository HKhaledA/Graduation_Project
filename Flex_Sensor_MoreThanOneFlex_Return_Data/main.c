/*
 * main.c
 */


#include <avr/io.h>
#include "std_types.h"
#include "BIT_MATH.h"
#define F_CPU 12000000
#include "util/delay.h"
#include "lcd.h"
#include "ADC.h"

/*------------------- Functions Prototypes --------------------*/
void Read_Flex( u8 Flex_adcChannel_Number, u16 adcDigial_Value);
/*-------------------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables ---------*/
u8 Letter_A[7]={"0000000"};
u8 Letter_B[7]={"1111111"};
u8 Letter_C[7]={"2222222"};
u8 Letter_D[7]={"3333333"};
u8 Letter_E[7]={"4444444"};
u8 Letter_F[7]={"5555555"};
u8 Letter_G[7]={"6666666"};
/*-----------------------------------------------------------------------*/

u8 Flex[4];

int main (void)
{
	DDRC=0xff;
//	DDRA=0x00;

	ADC_init();

	while(1)
	{
		Flex[0]= ADC_GetResult(0);
		Read_Flex(0, Flex[0]);
		Flex[1]= ADC_GetResult(1);
		Read_Flex(1, Flex[1]);
		Flex[2]= ADC_GetResult(2);
		Read_Flex(2, Flex[2]);
		Flex[3]= ADC_GetResult(3);
		Read_Flex(3, Flex[3]);
/*
		for {u8 Counter=0; Counter<4; Counter++)
		{
			if ( Flex[counter] == Letter_A[Counter])
		}
*/

		if ( (Flex[0]== 1) && (Flex[1]== 1) && (Flex[2]== 1) && (Flex[3]== 1) )
			PORTC=0x01;
		else if ( (Flex[0]== 2) && (Flex[1]== 2) && (Flex[2]== 2) && (Flex[3]== 2) )
			PORTC=0x02;
		else if ( (Flex[0]== 3) && (Flex[1]== 3) && (Flex[2]== 3) && (Flex[3]== 3) )
			PORTC=0x04;
		else if ( (Flex[0]== 4) && (Flex[1]== 4) && (Flex[2]== 4) && (Flex[3]== 4) )
			PORTC=0x08;
		else
			PORTC=0x00;

/*
		enum Flex_Sensors {F1=1 , F2, F3, F4} Flexxxx;

		switch(Flexxxx)
		{
		case F1:
		PORTC=0x01;
			break;
		case "2222":
			PORTC=0x02;
			break;
		case "3333":
			PORTC=0x04;
			break;
		case "4444":
			PORTC=0x08;
			break;
		default:
			PORTC=0x00;
			break;
		}
*/
	}
	return 0;
}

void Read_Flex( u8 Flex_adcChannel_Number, u16 adcDigial_Value)
{
	if ( (adcDigial_Value > 0) && (adcDigial_Value <= 15) )
		Flex[Flex_adcChannel_Number]=1;
	else if ( (adcDigial_Value > 15) && (adcDigial_Value <= 30) )
		Flex[Flex_adcChannel_Number]=2;
	else if ( (adcDigial_Value > 30) && (adcDigial_Value <= 45) )
		Flex[Flex_adcChannel_Number]=3;
	else if ( (adcDigial_Value > 45) && (adcDigial_Value <= 60) )
		Flex[Flex_adcChannel_Number]=4;
	else
		Flex[Flex_adcChannel_Number]=0;
}
