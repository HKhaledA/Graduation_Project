/*
 * ADXL354.c
 *
 * Created: 9/3/2018 8:08:05 PM
 *  Author: Hamdy
 */ 

#include <avr/io.h>
#include "std_types.h"
#include "STDTYPES.h"
#include "BIT_MATH.h"
#define F_CPU 12000000
#include "util/delay.h"
#include "lcd.h"
#include "i2c.h"
#include "ADXL345.h"
#include "uart.h"
#include "Music_Player.h"
#include "ADC.h"

#define F_ADXL 400000UL
/*---------------------- MACROS ---------------------*/
#define NumberOfFlexs		(u8) 1
# define Flex_Tolerance		(u8) 10
#define TRUE				(u8) 1
#define FALSE				(u8) 0
#define X_Angle_Accuracy 	 25
#define Y_Angle_Accuracy 	 25
#define Z_Angle_Accuracy 	 25
/*---------------------------------------------------*/

/*--------- Permanent Data that it will be burned on EEPROM IC using TWI
 *------------------- or it will be saved as a global variables --------*/

u8 Flex[4];
u8 Word_index;

typedef struct
{
	u8 Arr_Flex[NumberOfFlexs];

} Letters_and_Words;

Letters_and_Words Sensors_Readings;
Letters_and_Words Stored_Data[10]= {
										{ {150} },
										{ {165} },
										{ {175} },
										{ {200} },
								   };


volatile ADXL345_Data Live_Data;
ADXL345_Data Accs_Stored_Data[10]= {
										{ 250	, 7		, 30	},
										{ 240	, 67	, 29	},
										{ 245	, -22	, 27	},
								   };
enum Letters_and_Words
	{
		Letter_A=1,
		I_love_my_mom,
		Letter_C,
		Letter_D,
	};

/*------------------- Functions Prototypes --------------------*/
void Update_Flexs (Letters_and_Words * PTR_Flex);
u8  Compare_Flex_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data);
u8  Compare_Accs_Data ( ADXL345_Data * Ptr_Accs_Readings, ADXL345_Data * Ptr_Acss_Stored_Data);
/*-------------------------------------------------------------*/

int main(void)
{
//	DDRA=0x00;  	"Reserved for ADCs (Flex Sensors)"
	DDRB=0xFF;						 // LCD Data
	DDRC|= (1<<5) | (1<<6) | (1<<7); // LCD Control

	LCD_Init();
	UART_init();
	TWI_Init(I2C_PRESCALE1,I2C_intDisable,F_ADXL,0x01);
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	DFPlayer_init();
	ADC_init();

	LCD_WriteString("Testing LCD");
	_delay_ms(1000);
	
    while(1)
    {
		Update_Flexs(&Sensors_Readings);
		Accelerometor_ReadAxis(ADXL345_ALTERNATIVE_ADDRESS,&Live_Data);
		if (  Compare_Flex_Data(&Sensors_Readings, &Stored_Data))
		{
			if ( (Compare_Accs_Data(&Live_Data , &Accs_Stored_Data)))
			{
				switch(Word_index)
				{
				case Letter_A:
					LCD_SendCommand(1);
					LCD_WriteString_xy(1, 1, "A");
					play_sound(Letter_A);
					_delay_ms(1000);
					LCD_SendCommand(1);
					break;
				case I_love_my_mom:
					LCD_SendCommand(1);
					LCD_WriteString_xy(1, 1, "I Love my Mom");
					play_sound(I_love_my_mom);
					_delay_ms(1000);
					LCD_SendCommand(1);
					break;
				case Letter_C:
					LCD_SendCommand(1);
					LCD_WriteString_xy(1, 1, "C");
					play_sound(Letter_C);
					_delay_ms(1000);
					LCD_SendCommand(1);
					break;
				case Letter_D:
					LCD_SendCommand(1);
					LCD_WriteString_xy(1, 1, "D");
					play_sound(Letter_D);
					_delay_ms(1000);
					LCD_SendCommand(1);
					break;
				default:
					/* Don't Send anything*/
					break;
				}

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
}
/*---------------------------------------------------------------*/

u8  Compare_Flex_Data ( Letters_and_Words * Ptr_Sensor_Readings, Letters_and_Words * Ptr_Stored_Data)
{
	u8 ArrFlex_Counter;
	u8 ArrStruct_Counter;
	Word_index=0;
	for (ArrStruct_Counter=0; ArrStruct_Counter<10; ArrStruct_Counter++)
	{
		for (ArrFlex_Counter= 0; ArrFlex_Counter < NumberOfFlexs; ArrFlex_Counter++)
			{
				if ( abs( Ptr_Sensor_Readings-> Arr_Flex[ArrFlex_Counter] - Ptr_Stored_Data[ArrStruct_Counter]. Arr_Flex[ArrFlex_Counter] ) <= Flex_Tolerance )
				{
					if (ArrFlex_Counter == NumberOfFlexs-1)
					{

						if ( abs( Ptr_Sensor_Readings-> Arr_Flex[ArrFlex_Counter] - Ptr_Stored_Data[ArrStruct_Counter]. Arr_Flex[ArrFlex_Counter] ) <= Flex_Tolerance )
						{
							Word_index= ArrStruct_Counter + 1;
							return 1;
						}
					}
				}
			}
	}
	return 0;
}
/*-----------------------------------------------------------------------------*/

u8  Compare_Accs_Data ( ADXL345_Data * Ptr_Accs_Readings, ADXL345_Data * Ptr_Acss_Stored_Data)
{
		if  (
				( abs( (Ptr_Accs_Readings->X_Axis - Ptr_Acss_Stored_Data[Word_index - 1].X_Axis) ) <=  X_Angle_Accuracy )
			 && ( abs( (Ptr_Accs_Readings->Y_Axis - Ptr_Acss_Stored_Data[Word_index - 1].Y_Axis) ) <=  Y_Angle_Accuracy )
			 && ( abs( (Ptr_Accs_Readings->Z_Axis - Ptr_Acss_Stored_Data[Word_index - 1].Z_Axis) ) <=  Z_Angle_Accuracy )
			)
		{
			return 1;
		}
	return 0;
}
