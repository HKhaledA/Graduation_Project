/*
 * main.c
 */


#include <avr/io.h>
#include "std_types.h"
#include "BIT_MATH.h"
#define F_CPU 12000000
#include "util/delay.h"
#include "LCD.h"
#include "ADXL345.h"
#include "ADC.h"

#define F_ADXL 400000UL

/*---------------------- MACROS ---------------------*/
#define NumberOfFlexs	(u8) 4
#define TRUE	(u8) 1
#define FALSE	(u8) 0
/*---------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/
typedef struct
{
	u8 Arr_Flex[NumberOfFlexs];
	s16 X_Axis;
	s16 Y_Axis;
	s16 Z_Axis;
} Letters_and_Words;

//Letters_and_Words Letter_A= { {1,1,1,1} , 1.0 , 1.0, 1.0 };

Letters_and_Words Stored_Data[10]= {
										{ {1,1,1,1} , 1.0 , 1.0 , 1.0 },
										{ {2,2,2,2} , 1.0 , 1.0 , 1.0 },
										{ {3,3,3,3} , 1.0 , 1.0 , 1.0 },
										{ {4,4,4,4} , 1.0 , 1.0 , 1.0 },
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
void Update_Accelerometor_Axis (ADXL345_Address EFF_Address, Letters_and_Words * PTR_Accelerometor);

/*-------------------------------------------------------------*/

u8 Flex[4];
u8 Word_index;
volatile ADXL345_Data Live_Data;

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
	LCD_init();
	TWI_Init(I2C_PRESCALE1,I2C_intDisable,F_ADXL,0x01);
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	ADC_init();

	while(1)
	{
		Update_Flexs(&Sensors_Readings);
		Update_Accelerometor_Axis (ADXL345_ALTERNATIVE_ADDRESS, &Sensors_Readings);

	/*	CmpFlexData ( &Flex, &Stored_Data);*/

		if( Compare_Flex_Data(&Sensors_Readings, &Stored_Data) )
		{
			switch(Word_index)
			{
			case Letter_A:
				PORTC=0x01;
				break;
			case Letter_B:
				PORTC=0x02;
				break;
			case Letter_C:
				PORTC=0x04;
				break;
			case Letter_D:
				PORTC=0x08;
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
void  CmpFlexData ( u8* ReadingsArr, u8* StoredArr)
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
/*----------------------------------------------------------------*/
void Update_Accelerometor_Axis (ADXL345_Address EFF_Address, Letters_and_Words * PTR_Accelerometor)
{
		u16 X_Axis_Read;
		u16 Y_Axis_Read;
		u16 Z_Axis_Read;


		X_Axis_Read = (u8)I2C_ByteRead(EFF_Address , ACCS_DATAX0);
		_delay_ms(1);
		X_Axis_Read |= ((u8)I2C_ByteRead(EFF_Address , ACCS_DATAX1))<<8;
		_delay_ms(1);
		Y_Axis_Read = (u8)I2C_ByteRead(EFF_Address , ACCS_DATAY0);
		_delay_ms(1);
		Y_Axis_Read |= ((u8)I2C_ByteRead(EFF_Address , ACCS_DATAY1))<<8;
		_delay_ms(1);
		Z_Axis_Read = (u8)I2C_ByteRead(EFF_Address , ACCS_DATAZ0);
		_delay_ms(1);
		Z_Axis_Read |= ((u8)I2C_ByteRead(EFF_Address , ACCS_DATAZ1))<<8;
		_delay_ms(1);

		PTR_Accelerometor -> X_Axis= (X_Axis_Read);
		PTR_Accelerometor -> Y_Axis= (Y_Axis_Read);
		PTR_Accelerometor -> Z_Axis= (Z_Axis_Read);
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
