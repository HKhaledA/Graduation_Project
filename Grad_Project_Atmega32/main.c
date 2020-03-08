/*
 * main.c
 */


#include <avr/io.h>
#include "std_types.h"
#include "STDTYPES.h"
#include "BIT_MATH.h"
#define F_CPU 12000000
#include "util/delay.h"
#include "lcd.h"
#include "uart.h"
#include "Music_Player.h"
#include "ADC.h"

/*---------------------- MACROS ---------------------*/
#define NumberOfFlexs	(u8) 1
#define TRUE	(u8) 1
#define FALSE	(u8) 0
/*---------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/

u8 Flex[4];
u8 Word_index;

typedef struct
{
	u8 Arr_Flex[NumberOfFlexs];
	s8 Roll;
	s8 Pitch;
	s8 Yaw;
} Letters_and_Words;

//Letters_and_Words Letter_A= { {1,1,1,1} , 1.0 , 1.0, 1.0 };

Letters_and_Words Stored_Data[10]= {
										{ {1} , 1.0 , 1.0, 1.0 },
										{ {2} , 1.0 ,1.0 , 1.0 },
										{ {3} , 1.0 ,1.0 , 1.0 },
										{ {4} , 1.0 ,1.0 , 1.0 },
								   };

Letters_and_Words Sensors_Readings;

/*
Letters_and_Words Letter_B= { {2,2,2,2,2,2,2} , 1.0 , 1.0, 1.0};
Letters_and_Words Letter_C= { {3,3,3,3,3,3,3} , 1.0 , 1.0, 1.0};
Letters_and_Words Letter_D= { {4,4,4,4,4,4,4} , 1.0 , 1.0, 1.0};
*/

/*-----------------------------------------------------------------------*/
/*------------------- Functions Prototypes --------------------*/
void Adjust_Flex_Range( u8 Flex_adcChannel_Number, u16 adcDigial_Value);
/*void  CmpFlexData ( u8* ReadingsArr, u8* StoredArr);*/
void Update_Flexs (Letters_and_Words * PTR_Flex);
u8  Compare_Flex_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data);

/*-------------------------------------------------------------*/

int main (void)
{
 enum Letters_and_Words
	{
		Letter_A=1,
		Letter_B,
		Letter_C,
		Letter_D,
	};
//	u8 Word_index;
	u8 result;
//	DDRA=0x00;  "reserved for ADCs"
	DDRC=0xff;
//	DDRD=0xff;
	DDRB=0xff;

	LCD_Init();
	LCD_SendCommand(0);
	LCD_WriteData('L');
	_delay_ms(2000);

	UART_init();
	DFPlayer_init();
	ADC_init();

	while(1)
	{
		Update_Flexs(&Sensors_Readings);
	/*	CmpFlexData ( &Flex, &Stored_Data);*/

		if( Compare_Flex_Data(&Sensors_Readings, &Stored_Data) )
		{
			switch(Word_index)
			{
			case Letter_A:
				PORTC=0x01;
				LCD_SendCommand(0);
				LCD_WriteString("A");
				play_sound(Letter_A);
				_delay_ms(1000);
				break;
			case Letter_B:
				PORTC=0x02;
				LCD_SendCommand(0);
				LCD_WriteString("B");
				play_sound(Letter_B);
				_delay_ms(1000);
				break;
			case Letter_C:
				PORTC=0x04;
				LCD_SendCommand(0);
				LCD_WriteString("C");
				play_sound(Letter_C);
				_delay_ms(1000);
				break;
			case Letter_D:
				PORTC=0x08;
				LCD_SendCommand(0);
				LCD_WriteString("D");
				play_sound(Letter_D);
				_delay_ms(500);
				break;
			}
		}
		else
		{
			PORTC=0x00;
		}
	}
	return 0;
}
/*---------------------------------------------------------------*/
void Adjust_Flex_Range( u8 Flex_adcChannel_Number, u16 adcDigial_Value)
{
	if (adcDigial_Value > 60 + 85)
		Flex[Flex_adcChannel_Number]=0;
	else if ( (adcDigial_Value <= 60 + 85) && (adcDigial_Value > 30 + 85) )
		Flex[Flex_adcChannel_Number]=1;
	else if ( (adcDigial_Value <= 30 + 85) && (adcDigial_Value > 15 + 85) )
		Flex[Flex_adcChannel_Number]=2;
	else if ( (adcDigial_Value <= 15 + 85) && (adcDigial_Value > 5 + 85) )
		Flex[Flex_adcChannel_Number]=3;
	else if (adcDigial_Value < 5 + 85)
		Flex[Flex_adcChannel_Number]=4;
}
/*---------------------------------------------------------------*/
void CmpFlexData ( u8* ReadingsArr, u8* StoredArr)
{
	u8 Counter_struct;
	u8 Counter;
	u8 Matching_flag= FALSE;
	u8 Word_index;

	for (Counter_struct= 0 ; Counter_struct < 10 ; Counter_struct++)
	{
		for (Counter= 0 ; Counter < NumberOfFlexs ; Counter++)
		{
			if ( ReadingsArr[Counter] != StoredArr[Counter])
			{
				PORTC=0x00;
//				return 0;
				break;
			}
				if (Counter == NumberOfFlexs-1)
				{
					if ( ReadingsArr[Counter] == StoredArr[Counter])
						{
							PORTC=0x01;
							Matching_flag= TRUE;
						}
				}
		}
		if ( Matching_flag == TRUE)
//			return Word_index;
			break;
	}
//	return 0;
}
/*---------------------------------------------------------------*/
void Update_Flexs (Letters_and_Words * PTR_Flex)
{
	Flex[0]= ADC_GetResult(0);
	Adjust_Flex_Range(0, Flex[0]);
	PTR_Flex -> Arr_Flex[0]= Flex[0];

	Flex[1]= ADC_GetResult(1);
	Adjust_Flex_Range(1, Flex[1]);
	PTR_Flex -> Arr_Flex[1]= Flex[1];

	Flex[2]= ADC_GetResult(2);
	Adjust_Flex_Range(2, Flex[2]);
	PTR_Flex -> Arr_Flex[2]= Flex[2];

	Flex[3]= ADC_GetResult(3);
	Adjust_Flex_Range(3, Flex[3]);
	PTR_Flex -> Arr_Flex[3]= Flex[3];
}
/*---------------------------------------------------------------*/
u8  Compare_Flex_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data)
{
	u8 Counter;
	u8 Counter1;
/*	u8 Matching_flag=FALSE;*/
	Word_index=0;
	for (Counter1=0; Counter1<10; Counter1++)
	{
/*			Matching_flag= FALSE;*/

		for (Counter=0; Counter<NumberOfFlexs; Counter++)
			{
				if ( Ptr_Sensor_Readings ->Arr_Flex[Counter] != Ptr_Stored_Data[Counter1].Arr_Flex[Counter])
				{
//					PORTC=0x00;
	//				return 0;
					break;
				}
					if (Counter == NumberOfFlexs-1)
					{
						if ( Ptr_Sensor_Readings ->Arr_Flex[Counter] == Ptr_Stored_Data[Counter1].Arr_Flex[Counter])
							{
//								PORTC=0x01;
//							Matching_flag= TRUE;
							Word_index= Counter1 + 1;
							return 1;
							}
					}

			}
/*
		if ( Matching_flag == TRUE)
		break;
*/
	}
	return 0;
}
