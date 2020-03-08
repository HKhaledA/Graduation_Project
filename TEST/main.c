/*
 * main.c
 */


#include "MICROCONIFG.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "lcd.h"
#include "ADXL345.h"
#include "Music_Player.h"
#include "uart.h"
#include "ADC.h"

/*---------------------- MACROS ---------------------*/
#define NumberOfFlexs		(u8)  4
#define TRUE				(u8)  1
#define FALSE				(u8)  0
#define X_Angle_Accuracy 	(u16) 50
#define Y_Angle_Accuracy 	(u16) 50
#define Z_Angle_Accuracy 	(u16) 50
/*---------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/
typedef struct
{
	u8 Arr_Flex[NumberOfFlexs];
	float X_Axis;
	float Y_Axis;
	float Z_Axis;
} Letters_and_Words;

Letters_and_Words Sensors_Readings;
Letters_and_Words Stored_Data[10]= {
										{ {1,1,1,1} , 1.0 , 1.0, 1.0 },
										{ {2,2,2,2} , 1.0 ,1.0 , 1.0 },
										{ {3,3,3,3} , 1.0 ,1.0 , 1.0 },
										{ {4,4,4,4} , 1.0 ,1.0 , 1.0 },
								   };

/*-----------------------------------------------------------------------*/
/*------------------- Functions Prototypes --------------------*/
void Adjust_Flex_Range( u8 Flex_adcChannel_Number, u16 adcDigial_Value);
void Update_Flexs (Letters_and_Words * PTR_Flex);
u8  Compare_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data);
void Accelerometor_init(ADX345_PowerModes Mode , ADXL345_Address EFF_Address);
void Accelerometor_ReadAxis(ADXL345_Address EFF_Address , Letters_and_Words * Ptr_Acc);

/*-------------------------------------------------------------*/

u8 Flex[4];
u8 Word_index;

int main (void)
{
 enum Letters_and_Words
	{
		Letter_A=1,
		Letter_B,
		Letter_C,
		Letter_D,
	};
//	DDRA=0x00;  "reserved for ADCs"
	DDRC=0xff;

	LCD_Init();
	UART_init();
	TWI_Init(I2C_PRESCALE1,I2C_intDisable,F_ADXL,0x01);
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	DFPlayer_init();
	ADC_init();

	while(1)
	{

		Update_Flexs(&Sensors_Readings);
		Accelerometor_ReadAxis(ADXL345_ALTERNATIVE_ADDRESS,&Sensors_Readings);

LABEL_ACC:	LCD_Clear();
			LCD_WriteString_xy(1 , 1 , "X=");
			LCD_DisplayInt((uint16) (Sensors_Readings.X_Axis));
			LCD_WriteString_xy(8 , 1 , " Y=");
			LCD_DisplayInt((uint16) (Sensors_Readings.Y_Axis));
			LCD_WriteString_xy(1 , 2 , "Z=");
			LCD_DisplayInt((uint16) (Sensors_Readings.Z_Axis));
			_delay_ms(500);

	goto LABEL_ACC;

		if( Compare_Data(&Sensors_Readings, &Stored_Data) )
		{
			switch(Word_index)
			{
			case Letter_A:
				PORTC=0x01;
				LCD_SendCommand(0);
				LCD_WriteString("A");
				play_sound(Letter_A);
				_delay_ms(500);
				break;
			case Letter_B:
				PORTC=0x02;
				LCD_SendCommand(0);
				LCD_WriteString("B");
				play_sound(Letter_B);
				_delay_ms(500);
				break;
			case Letter_C:
				PORTC=0x04;
				LCD_SendCommand(0);
				LCD_WriteString("C");
				play_sound(Letter_C);
				_delay_ms(500);
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
u8  Compare_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data)
{
	u8 Counter;
	u8 Counter1;
	Word_index=0;

	for (Counter1=0; Counter1<10; Counter1++)
	{
		for (Counter=0; Counter<NumberOfFlexs; Counter++)
			{
				if ( Ptr_Sensor_Readings ->Arr_Flex[Counter] != Ptr_Stored_Data[Counter1].Arr_Flex[Counter])
				{
	//				return 0;
					break;
				}
					if (Counter == NumberOfFlexs-1)
					{
						if ( Ptr_Sensor_Readings ->Arr_Flex[Counter] == Ptr_Stored_Data[Counter1].Arr_Flex[Counter])
							{
								if (  ( (  Ptr_Sensor_Readings->X_Axis - Ptr_Stored_Data[Counter1]->X_Axis ) >= - X_Angle_Accuracy )
									 && ( (Ptr_Sensor_Readings->X_Axis - Ptr_Stored_Data[Counter1]->X_Axis ) <=   X_Angle_Accuracy )
									 && ( (Ptr_Sensor_Readings->Y_Axis - Ptr_Stored_Data[Counter1]->Y_Axis ) >= - Y_Angle_Accuracy )
									 && ( (Ptr_Sensor_Readings->Y_Axis - Ptr_Stored_Data[Counter1]->Y_Axis ) <=   Y_Angle_Accuracy )
									 && ( (Ptr_Sensor_Readings->Z_Axis - Ptr_Stored_Data[Counter1]->Z_Axis ) >= - Z_Angle_Accuracy )
									 && ( (Ptr_Sensor_Readings->Z_Axis - Ptr_Stored_Data[Counter1]->Z_Axis ) <=   Z_Angle_Accuracy )
								   )
									{
										Word_index= Counter1 + 1;
										return 1;
									}
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
/*-----------------------------------------------------------------------------*/

void Accelerometor_init(ADX345_PowerModes Mode , ADXL345_Address EFF_Address)
{
	I2C_ByteWrite(EFF_Address,POWER_CTRL,Mode);
	I2C_ByteWrite(EFF_Address,ACCS_DATA_FORMAT,0x0B);
	I2C_ByteWrite(EFF_Address,ACCS_OFSX,-1);
	I2C_ByteWrite(EFF_Address,ACCS_OFSY,0);
	I2C_ByteWrite(EFF_Address,ACCS_OFSZ,-1);
	//I2C_ByteWrite(EFF_Address,ACCS_DATA_FORMAT,0);
	//I2C_ByteWrite(EFF_Address,ACCS_DATA_FORMAT,8);
}
/*-----------------------------------------------------------------------------*/

void Accelerometor_ReadAxis(ADXL345_Address EFF_Address , Letters_and_Words * Ptr_Acc)
{
	uint16 X_Axis_Read;
	uint16 Y_Axis_Read;
	uint16 Z_Axis_Read;


	X_Axis_Read = (uint8)I2C_ByteRead(EFF_Address , ACCS_DATAX0);
	_delay_ms(1);
	X_Axis_Read |= ((uint8)I2C_ByteRead(EFF_Address , ACCS_DATAX1))<<8;
	_delay_ms(1);
	Y_Axis_Read = (uint8)I2C_ByteRead(EFF_Address , ACCS_DATAY0);
	_delay_ms(1);
	Y_Axis_Read |= ((uint8)I2C_ByteRead(EFF_Address , ACCS_DATAY1))<<8;
	_delay_ms(1);
	Z_Axis_Read = (uint8)I2C_ByteRead(EFF_Address , ACCS_DATAZ0);
	_delay_ms(1);
	Z_Axis_Read |= ((uint8)I2C_ByteRead(EFF_Address , ACCS_DATAZ1))<<8;
	_delay_ms(1);

	Ptr_Acc -> X_Axis= (X_Axis_Read);
	Ptr_Acc -> Y_Axis= (Y_Axis_Read);
	Ptr_Acc -> Z_Axis= (Z_Axis_Read);
}
