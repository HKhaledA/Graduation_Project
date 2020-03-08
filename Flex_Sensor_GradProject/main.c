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

/*---------------------- MACROS ---------------------*/
#define NumberOfFlexs	(u8) 4
/*---------------------------------------------------*/

/*------------------- Functions Prototypes --------------------*/
void Read_Flex( u8 Flex_adcChannel_Number, u16 adcDigial_Value);
void CmpFlexData ( u8* ReadingsArr, u8* StoredArr);
/*-------------------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/
typedef struct
{
	u8 Arr_Flex[NumberOfFlexs];
	s8 Roll,pitch, yaw;

} Letters_and_Words;

Letters_and_Words Letter_A= { {1,1,1,1} , 1.0 , 1.0, 1.0 };

Letters_and_Words Sensors_Readings;


/*
Letters_and_Words Letter_B= { {2,2,2,2,2,2,2} , 1.0 , 1.0};
Letters_and_Words Letter_C= { {3,3,3,3,3,3,3} , 1.0 , 1.0};
Letters_and_Words Letter_D= { {4,4,4,4,4,4,4} , 1.0 , 1.0};
Letters_and_Words Letter_E= { {5,5,5,5,5,5,5} , 1.0 , 1.0};
*/

/*-----------------------------------------------------------------------*/
u8 Flex[4];

int main (void)
{
//	DDRA=0x00;  "reserved for ADCs"
	DDRC=0xff;
	ADC_init();

	while(1)
	{
		Read_Flex(0, ADC_GetResult(0));
		Read_Flex(1, ADC_GetResult(1));
		Read_Flex(2, ADC_GetResult(2));
		Read_Flex(3, ADC_GetResult(3));

		CmpFlexData ( Flex, Letter_A.Arr_Flex);

	/*
		if ( (Flex[0] == Letter_A.Arr_Flex[0]) && (Flex[1] == Letter_A.Arr_Flex[1]) && (Flex[2] == Letter_A.Arr_Flex[2]) && (Flex[3] == Letter_A.Arr_Flex[3]) )
			PORTC=0x01;

		else if ( (Flex[0] == 2) && (Flex[1] == 2) && (Flex[2] == 2) && (Flex[3] == 2) )
			PORTC=0x02;
		else if ( (Flex[0] == 3) && (Flex[1] == 3) && (Flex[2] == 3) && (Flex[3] == 3) )
			PORTC=0x04;
		else if ( (Flex[0] == 4) && (Flex[1] == 4) && (Flex[2] == 4) && (Flex[3] == 4) )
			PORTC=0x08;

		else
			PORTC=0x00;
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
/*---------------------------------------------------------------*/
void CmpFlexData ( u8* ReadingsArr, u8* StoredArr)
{
	u8 Counter;

	for (Counter= 0 ; Counter < NumberOfFlexs ; Counter++)
	{
		if ( ReadingsArr[Counter] != StoredArr[Counter])
		{
			PORTC=0x00;
			break;
		}
			if (Counter == NumberOfFlexs-1)
			{
				if ( ReadingsArr[Counter] == StoredArr[Counter])
					PORTC=0x01;
			}
	}
}
/*---------------------------------------------------------------*/
