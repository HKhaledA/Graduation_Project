/*
 * main.c
 *
 *  Created on: June 21, 2019
 *      Author: Abdurahman ElGebaly
 */

#include <avr/io.h>
#include <avr/iom128.h>
#include "std_types.h"
#include "STDTYPES.h"
#include "BIT_MATH.h"
#define F_CPU 16000000UL
#include "util/delay.h"
#include "lcd.h"
#include "i2c.h"
#include "ADXL345.h"
#include "uart.h"
#include "Music_Player.h"
#include "ADC.h"

#define F_ADXL 400000UL
/*---------------------- MACROS ---------------------*/
#define NumberOfFlexs		(u8) 7
#define NumberOfStoredWords	(u8) 10
# define Flex_Tolerance		(u8) 12
#define X_Angle_Accuracy 	 40
#define Y_Angle_Accuracy 	 40
#define Z_Angle_Accuracy 	 40

#define Calibration			 24
#define User				 25

#define GloveMode	User
/*---------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/
u8 Word_index;

typedef struct
{
	u8 Arr_Flex[7];
	float X_Axis;
	float Y_Axis;
	float Z_Axis;
} Letters_and_Words;

Letters_and_Words Sensors_Readings;
Letters_and_Words Stored_Data[NumberOfStoredWords]= {
		/* Letter C */					{ {116,118,115,123,115,155,115} , -100	,  89	, -205	},
		/* Letter J */					{ {117, 90, 84,105,155,138, 79} , -55	, -89	, -210	},
		/* Number 0 */					{ {115, 94, 86, 98, 88,153, 91} , -5	,  31	, -232	},
		/* Number 5  */					{ {140,142,148,155,154,162,135} , -5	,  22	, -231	},
		/* Good afternoon */			{ {135,143,153,156,154,158,130} , -71	, -143	, -177	},
		/* Hope */						{ {162,160,164,169,156,138,155} ,  -86	,  26	, -220	},
		/* That You */					{ {118,146, 85, 93, 91,131,147} , -60	, -128	, -193	},
		/* Enjoy */						{ {147,142,134,140,148,129,141} , -157	, -101	, -161	},
		/* Our show */					{ {116,160, 93,102, 90,122,154} , -247	,  64	, -87	},
   												    };
enum Letters_and_Words
	{
		Letter_C=1,
		Letter_J,
		Number_0,
		Number_5,
		Good_afternoon_professors,
		Hope,
		That_you,
		Enjoy,
		Our_show,
		My,
		Name,
		I_love_my_mom,
	};

/*------------------- Functions Prototypes --------------------*/
void Update_Flexs (Letters_and_Words * PTR_Flex);
void Accelerometor_init(ADX345_PowerModes Mode , ADXL345_Address EFF_Address);
void Update_Accelerometor_Axis(ADXL345_Address EFF_Address , Letters_and_Words * Data_ptr);
u8 Compare_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data);

/*-------------------------------------------------------------*/

int main(void)
{
//	DDRF=0x00;  	"Reserved for ADCs (Flex Sensors)"
	DDRA=0xFF;						 // LCD Data
	DDRC|= (1<<5) | (1<<6) | (1<<7); // LCD Control
	LCD_Init();
	UART_init();
	TWI_Init(I2C_PRESCALE1,I2C_intDisable,F_ADXL,0x01);
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	DFPlayer_init();
	LCD_WriteString("Testing LCD");
	_delay_ms(1000);
	ADC_init();
	
    while(1)
    {
#if GloveMode == Calibration	/* This mode is only for developers */
		Update_Flexs(&Sensors_Readings);
		Update_Accelerometor_Axis(ADXL345_ALTERNATIVE_ADDRESS,&Sensors_Readings);
		LCD_SendCommand(1);
		LCD_WriteInteger_xy(1,1, Sensors_Readings.Arr_Flex[0],4);
		LCD_WriteInteger_xy(5,1, Sensors_Readings.Arr_Flex[1],4);
		LCD_WriteInteger_xy(9,1, Sensors_Readings.Arr_Flex[2],4);
		LCD_WriteInteger_xy(13,1,Sensors_Readings.Arr_Flex[3],4);
		_delay_ms(500);
		LCD_SendCommand(1);
		LCD_WriteInteger_xy(1,1, Sensors_Readings.Arr_Flex[4],4);
		LCD_WriteInteger_xy(5,1, Sensors_Readings.Arr_Flex[5],4);
		LCD_WriteInteger_xy(9,1, Sensors_Readings.Arr_Flex[6],4);
		_delay_ms(500);
		LCD_SendCommand(1);
		LCD_WriteString_xy(1,1,"X=");
		LCD_WriteInteger_xy(3,1, (Sensors_Readings.X_Axis), 6);
		LCD_WriteString_xy(8,1,"Y=");
		LCD_WriteInteger_xy(10,1, (Sensors_Readings.Y_Axis), 6);
		LCD_WriteString_xy(1,2,"Z=");
		LCD_WriteInteger_xy(3,2, (Sensors_Readings.Z_Axis), 6);
		_delay_ms(500);
#endif

		Update_Flexs(&Sensors_Readings);
		Update_Accelerometor_Axis(ADXL345_ALTERNATIVE_ADDRESS,&Sensors_Readings);

		if ( Compare_Data(&Sensors_Readings, &Stored_Data))
		{
    			switch(Word_index)
			{
			case Letter_C:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "C");
				play_sound(Letter_C);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;

			case Letter_J:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "J");
				play_sound(Letter_J);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Number_0:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "0");
				play_sound(Number_0);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Number_5:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "5");
				play_sound(Number_5);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Good_afternoon_professors:
				LCD_SendCommand(1);
				LCD_WriteString_xy(3, 1, "Good afternoon");
				LCD_WriteString_xy(5, 2, "professors");
				play_sound(Good_afternoon_professors);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Hope:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Hope");
				play_sound(Hope);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case That_you:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "That you");
				play_sound(That_you);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Enjoy:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Enjoy");
				play_sound(Enjoy);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Our_show:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Our show");
				play_sound(Our_show);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			default:
				/* Don't Send anything*/
				break;
			}
		}
		else
		{
		/* Do nothing (Its equivalent --->  DF Send STOP) */
		}
	}
	return 0;
}
/*-----------------------------------------------------------------------------------------------*/

void Update_Flexs (Letters_and_Words * PTR_Flex)
{
	PTR_Flex -> Arr_Flex[0]= ADC_GetResult(0);
	PTR_Flex -> Arr_Flex[1]= ADC_GetResult(1);
	PTR_Flex -> Arr_Flex[2]= ADC_GetResult(2);
	PTR_Flex -> Arr_Flex[3]= ADC_GetResult(3);
	PTR_Flex -> Arr_Flex[4]= ADC_GetResult(4);
	PTR_Flex -> Arr_Flex[5]= ADC_GetResult(5);
	PTR_Flex -> Arr_Flex[6]= ADC_GetResult(6);
}
/*---------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------------------*/

void Update_Accelerometor_Axis(ADXL345_Address EFF_Address , Letters_and_Words * Data_ptr)
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

	Data_ptr ->X_Axis= (X_Axis_Read);
	Data_ptr ->Y_Axis= (Y_Axis_Read);
	Data_ptr ->Z_Axis= (Z_Axis_Read);
}
/*-----------------------------------------------------------------------------*/

u8  Compare_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data)
{
	u8 ArrFlex_Counter;
	u8 ArrStruct_Counter;
	Word_index=0;
	for (ArrStruct_Counter= 0; ArrStruct_Counter < NumberOfStoredWords; ArrStruct_Counter++)
	{
		for (ArrFlex_Counter= 0; ArrFlex_Counter < NumberOfFlexs; ArrFlex_Counter++)
			{
				if ( abs( Ptr_Sensor_Readings-> Arr_Flex[ArrFlex_Counter] - Ptr_Stored_Data[ArrStruct_Counter]. Arr_Flex[ArrFlex_Counter] ) <= Flex_Tolerance )
				{
					if (ArrFlex_Counter == NumberOfFlexs-1)
					{
						if ( abs( Ptr_Sensor_Readings-> Arr_Flex[ArrFlex_Counter] - Ptr_Stored_Data[ArrStruct_Counter]. Arr_Flex[ArrFlex_Counter] ) <= Flex_Tolerance )
						{
							if  (
									( abs( (Ptr_Sensor_Readings->X_Axis - Ptr_Stored_Data[ArrStruct_Counter].X_Axis) ) <=  X_Angle_Accuracy )
								 && ( abs( (Ptr_Sensor_Readings->Y_Axis - Ptr_Stored_Data[ArrStruct_Counter].Y_Axis) ) <=  Y_Angle_Accuracy )
								 && ( abs( (Ptr_Sensor_Readings->Z_Axis - Ptr_Stored_Data[ArrStruct_Counter].Z_Axis) ) <=  Z_Angle_Accuracy )
								)
							{
								Word_index= ArrStruct_Counter + 1;
								return 1;
							}
						}
					}
				}
			}
	}
	return 0;
}
