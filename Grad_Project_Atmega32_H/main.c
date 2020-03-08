/*
 * main.c
 */

#include "MICROCONIFG.h"
//#include <avr/io.h>
#include "std_types.h"
#include "BIT_MATH.h"
//#define F_CPU 12000000
#include "util/delay.h"
#include "lcd.h"
#include "ADXL345.h"
#include "Music_Player.h"
#include "uart.h"
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
	s16 rolldeg_AC;
	s16 pitchdeg_AC;
} Letters_and_Words;

//Letters_and_Words Letter_A= { {1,1,1,1} , 1.0 , 1.0, 1.0 };

Letters_and_Words Stored_Data[10]= {
										{ {1,1,1,1} , 1.0 , 1.0 },
										{ {2,2,2,2} , 1.0 , 1.0 },
										{ {3,3,3,3} , 1.0 , 1.0 },
										{ {4,4,4,4} , 1.0 , 1.0 },
								   };

Letters_and_Words Sensors_Readings;
typedef struct
{
		s16 fXg;
		s16 fYg;
		s16 fZg;
} temp_data;

temp_data Temp; // at this struct some variables that is used to store temp values that are used in certain equations
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
void Accelerometor_init(void);
void update_Accelerometor(Letters_and_Words * Ptr_Sensor_Readings , temp_data * Temp);
uint8 update_Accelerometor_f(uint8 reg1_add , uint8 reg2_add , uint8 ADDRESS_Write , uint8 ADDRESS_Read , temp_data * Temp);

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
//	u8 Word_index;
//	u8 result;
//	DDRA=0x00;  "reserved for ADCs"
	DDRC=0xff;

	LCD_Init();
	//	TWI_Init();
	Accelerometor_init();
	UART_init();
	DFPlayer_init();
	ADC_init();

	while(1)
	{
		Update_Flexs(&Sensors_Readings);
	/*	CmpFlexData ( &Flex, &Stored_Data);*/
		update_Accelerometor(&Sensors_Readings, &Temp);
		if( Compare_Flex_Data(&Sensors_Readings, &Stored_Data) )
		{
			switch(Word_index)
			{
			case Letter_A:
				PORTC=0x01;
				LCD_Clear();
				LCD_WriteString("A");
				play_sound(Letter_A);
				_delay_ms(500);
				break;
			case Letter_B:
				PORTC=0x02;
				LCD_Clear();
				LCD_WriteString("B");
				play_sound(Letter_B);
				_delay_ms(500);
				break;
			case Letter_C:
				PORTC=0x04;
				LCD_Clear();
				LCD_WriteString("C");
				play_sound(Letter_C);
				_delay_ms(500);
				break;
			case Letter_D:
				PORTC=0x08;
				LCD_Clear();
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
/*
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
*/

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
						if ( Ptr_Sensor_Readings-> Arr_Flex[Counter] == Ptr_Stored_Data[Counter1].Arr_Flex[Counter])
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
/*--------------------------------------------------------------------------------*/

void Accelerometor_init(void)
{
	LCD_Clear();
	TWI_Init(I2C_PRESCALE1,I2C_intDisable,F_ADXL,0x01);
	i2C_writeReg(POWER_CTRL,0x08,ACCS_ADDRESS_Write); // Enabling Accelerometer

	// init I2C Communication Protocol
	#if (Accs_Range == 2 )
	i2C_writeReg(ACCS_DATA_FORMAT,0x08,ACCS_ADDRESS_Write); // Specify
	Data Formate to Range
	#elif ( Accs_Range == 4)
	i2C_writeReg(ACCS_DATA_FORMAT,0x09,ACCS_ADDRESS_Write); // Specify
	Data Formate to Range
	#elif ( Accs_Range == 8)
	i2C_writeReg(ACCS_DATA_FORMAT,0x0A,ACCS_ADDRESS_Write); // Specify
	Data Formate to Range
	#elif ( Accs_Range == 16)
	i2C_writeReg(ACCS_DATA_FORMAT,0x0B,ACCS_ADDRESS_Write); // Specify
	Data Formate to Range
	#endif

	i2C_writeReg(ACCS_OFSX , -1 , ACCS_ADDRESS_Write);
	i2C_writeReg(ACCS_OFSX , 0  , ACCS_ADDRESS_Write);
	i2C_writeReg(ACCS_OFSX , 8  , ACCS_ADDRESS_Write);
	_delay_ms(20);
}
/*--------------------------------------------------------------------------------*/

void Acc_setsoftware_offset (double x, double y, double z)
{
	{
	_xoffse = x;
	ACCS_OFSZ = y;
	ACCS_OFSZ = z;
	}
}
/*--------------------------------------------------------------------------------*/

void update_Accelerometor(Letters_and_Words * Ptr_Sensor_Readings , temp_data * Temp)
{
	float X;
	float Y;
	float Z;

	update_Accelerometor_f( ACCS_DATAX0 , ACCS_DATAX1 , ACCS_ADDRESS_Write , ACCS_ADDRESS_Read , Temp);

	Temp-> fXg= ( (Temp->fXg) - 7 );
	Temp-> fYg= ( (Temp->fYg) - 6);
	Temp-> fZg= ( (Temp->fZg) + 10);

	X = Accs_Range* (Temp->fXg/1023.0); // used for angle calculations
	Y = Accs_Range* (Temp->fYg/1023.0); // used for angle calculations
	Z = Accs_Range* (Temp->fZg/1023.0); // used for angle calculations

	#ifdef LPF
	Temp-> fXg = X * Alpha + (Temp->fXg * (1.0 - Alpha));
	Temp-> fYg = Y * Alpha + (Temp->fYg * (1.0 - Alpha));
	Temp-> fZg = Z * Alpha + (Temp->fZg * (1.0 - Alpha));

	X= Temp-> fXg;
	Y= Temp-> fYg;
	Z= Temp-> fZg;
	#endif

	Ptr_Sensor_Readings-> rolldeg_AC = 180*(atan(Y/sqrt(X*X+Z*Z)))/3.14;  // calculated angle in degrees
	Ptr_Sensor_Readings-> pitchdeg_AC = 180*(atan(X/sqrt(Y*Y+Z*Z)))/3.14; // calculated angle in degrees
}
/*--------------------------------------------------------------------------------*/

uint8 update_Accelerometor_f(uint8 reg1_add , uint8 reg2_add , uint8 ADDRESS_Write , uint8 ADDRESS_Read , temp_data * Temp)
{
	uint8 X_low_val=0;
	uint8 x_High_val=0;
	uint8 y_low_val=0;
	uint8 y_High_val=0;
	uint8 z_low_val=0;
	uint8 z_High_val=0;

	TWI_Start();
	if (TWI_Get_Status() != TW_START)
	{
		LCD_Clear();
		LCD_DisplayString("Start_problem");
		_delay_ms(2000);
		TWI_Stop();
		return 0;
	}

	TWI_Write(ADDRESS_Write & 0xfe);
	if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Gyro_Add_pro");
		_delay_ms(2000);
		TWI_Stop();
		return 0;
	}

	TWI_Write(reg1_add);
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg1_addr");
		_delay_ms(2000);
		TWI_Stop();
		return 0;
	}

	TWI_Start();
	if (TWI_Get_Status() != TW_REP_START)
	{
		LCD_Clear();
		LCD_DisplayString("Repeated_start");
		_delay_ms(2000);
		TWI_Stop();
		return 0;
	}

	TWI_Write(ADDRESS_Read );
	if (TWI_Get_Status() != TW_MT_SLA_R_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Gyro_rep ");
		_delay_ms(2000);
		TWI_Stop();
		return 0;
	}

	X_low_val = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg1_read");
		TWI_Stop();
		_delay_ms(2000);
		return 0;
	}

	x_High_val = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg2_read");
		TWI_Stop();
		_delay_ms(2000);
		return 0;
	}

	y_low_val = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg2_read");
		TWI_Stop();
		_delay_ms(2000);
		return 0;
	}

	y_High_val = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg2_read");
		TWI_Stop();
		_delay_ms(2000);
		return 0;
	}

	z_low_val = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg2_read");
		TWI_Stop();
		_delay_ms(2000);
		return 0;
	}

	z_High_val = TWI_Read_With_NACK();
	if (TWI_Get_Status() != TW_MR_DATA_NACK)
	{
		LCD_Clear();
		LCD_DisplayString("Reg2_read");
		TWI_Stop();
		_delay_ms(2000);
		return 0;
	}

	TWI_Stop();

	Temp-> fXg=(( ((sint16) x_High_val )<<8)|X_low_val);
	Temp-> fYg=(( ((sint16) y_High_val )<<8)|y_low_val);
	Temp-> fZg=(( ((sint16) z_High_val )<<8)|z_low_val);

	return 1;
}
