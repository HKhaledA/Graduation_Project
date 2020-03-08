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
# define Flex_Tolerance		(u8) 10
#define TRUE				(u8) 1
#define FALSE				(u8) 0
#define X_Angle_Accuracy 	 50
#define Y_Angle_Accuracy 	 50
#define Z_Angle_Accuracy 	 50
/*---------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/
//u8 Flex[4];
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

		/* Hello Dr. Eman */			{ {170,171,190,169,186,167,175} , -115	, 22	, 242	},
		/* We */						{ {181,159,148,170,175,160,161} , -80	, 261	, 40	},
		/* Wish you */					{ {185,177,177,174,185,167,170} , 169	, 174	, -64	},
		/* A good day */				{ {135,187,138,177,136,143,147} , -56	, 265	, 14	},
		/* Letter A */					{ {159, 99, 93,106, 91,69, 105} , -39	, -220	, -101	},
		/* Letter B */					{ {116,150,158,157,154,151,154} , -33	, -71	, -220	},
		/* Letter C */					{ {132,131,123,121,110,114,124} , -87	, -65	, -209	},
		/* Number 1  */					{ {127,154,107,114,103,80 ,153} , 2		, -44	, -228	},
		/* Number 2 */					{ {136,153,160,115,116,85 ,157} , 9		, -15	, -229	},
		/* Number 3 */					{ {129,157,170,165,115,157,156} , 14	, -25	, -273	},
		/* Good Morning */				{ {156,149,152,156,147,145,148} , 163	, -161	, -93	},
		/* My */						{ {160,152,159,153,143,144,146} , 9		, -214	, -108	},
		/* Name */						{ {131,162,165,115,120,97 ,157} , -22	, -111	, -214	},
		/* is Yousif */					{ {196,116,108,121,108,100,124} , -121	, -252	, -39	},

/*
		 Hello Dr. Eman 			{ {181,159,148,170,175,160,161} , -80	, 261	, 40	},
		 Hello Dr. Eman 			{ {185,177,177,174,185,167,170} , 169	, 174	, -64	},
		 Hello Dr. Eman 			{ {135,187,138,177,136,143,147} , -56	, 265	, 14	},
		 Hello Dr. Eman 			{ {170,171,190,169,186,167,175} , -115	, 22	, 242	},
		 Hello Dr. Eman 			{ {181,159,148,170,175,160,161} , -80	, 261	, 40	},
		 Hello Dr. Eman 			{ {185,177,177,174,185,167,170} , 169	, 174	, -64	},
		 Hello Dr. Eman 			{ {135,187,138,177,136,143,147} , -56	, 265	, 14	},
*/
   												    };
enum Letters_and_Words
	{
		Hello_Dr_Eman=1,
		We,
		Wish_you,
		A_Good_day,
		Letter_A,
		Letter_B,
		Letter_C,
		Number_1,
		Number_2,
		Number_3,
		Good_Morning,
		My,
		Name,
		is_Yousif,
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
//    	TEST:

		Update_Flexs(&Sensors_Readings);
		Update_Accelerometor_Axis(ADXL345_ALTERNATIVE_ADDRESS,&Sensors_Readings);


/*
		LCD_SendCommand(1);
		LCD_WriteInteger_xy(1,1,Sensors_Readings.Arr_Flex[0],4);
		LCD_WriteInteger_xy(5,1,Sensors_Readings.Arr_Flex[1],4);
		LCD_WriteInteger_xy(9,1,Sensors_Readings.Arr_Flex[2],4);
		LCD_WriteInteger_xy(13,1,Sensors_Readings.Arr_Flex[3],4);
		_delay_ms(500);
		LCD_SendCommand(1);
		LCD_WriteInteger_xy(1,1,Sensors_Readings.Arr_Flex[4],4);
		LCD_WriteInteger_xy(5,1,Sensors_Readings.Arr_Flex[5],4);
		LCD_WriteInteger_xy(9,1,Sensors_Readings.Arr_Flex[6],4);
		_delay_ms(500);
		LCD_SendCommand(1);
		LCD_WriteString_xy(1,1,"X=");
		LCD_WriteInteger_xy(3,1, (Sensors_Readings.X_Axis), 6);
		LCD_WriteString_xy(8,1,"Y=");
		LCD_WriteInteger_xy(10,1, (Sensors_Readings.Y_Axis), 6);
		LCD_WriteString_xy(1,2,"Z=");
		LCD_WriteInteger_xy(3,2, (Sensors_Readings.Z_Axis), 6);
		_delay_ms(500);

	goto TEST;

*/
		if ( Compare_Data(&Sensors_Readings, &Stored_Data))
		{
    			switch(Word_index)
			{
			case Hello_Dr_Eman:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Hello Dr. Eman");
				play_sound(Hello_Dr_Eman);
				_delay_ms(1500);
				LCD_SendCommand(1);
				break;
			case We:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "We");
				play_sound(We);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Wish_you:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Wish you");
				play_sound(Wish_you);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case A_Good_day:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "A good day");
				play_sound(A_Good_day);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Letter_A:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "A");
				play_sound(Letter_A);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Letter_B:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "B");
				play_sound(Letter_B);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Letter_C:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "C");
				play_sound(Letter_C);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Number_1:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "1");
				play_sound(Number_1);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Number_2:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "2");
				play_sound(Number_2);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Number_3:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "3");
				play_sound(Number_3);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Good_Morning:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Good Morning");
				play_sound(Good_Morning);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case My:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "My");
				play_sound(My);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case Name:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "Name");
				play_sound(Name);
				_delay_ms(2000);
				LCD_SendCommand(1);
				break;
			case is_Yousif:
				LCD_SendCommand(1);
				LCD_WriteString_xy(1, 1, "is Yousif");
				play_sound(is_Yousif);
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
		//	PORTC=0x00;  // Its equivalent --->  DF Send STOP
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
