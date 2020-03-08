/*
 * main.c
 *
 *  Created on: Jun 19, 2019
 *      Author: Abdur
 */

#include "MICROCONIFG.h"
//#include <avr/io.h>
#include "std_types.h"
#include "BIT_MATH.h"
#define F_CPU 12000000
#include "util/delay.h"
#include "lcd.h"
#include "ADXL345.h"

#define F_ADXL 400000UL

 typedef struct
{
	u8 Arr_Flex[4];
	s16 rolldeg_AC;
	s16 pitchdeg_AC;
} Letters_and_Words;
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

temp_data Temp;

void Accelerometor_init(void);
void update_Accelerometor(Letters_and_Words * Ptr_Sensor_Readings , temp_data * Temp);
uint8 update_Accelerometor_f(uint8 reg1_add , uint8 reg2_add , uint8 ADDRESS_Write , uint8 ADDRESS_Read , temp_data * Temp);


int main (void)
{
	DDRC=0xff;

	LCD_Init();
	//	TWI_Init();
	Accelerometor_init();

	while(1)
	{
		update_Accelerometor(&Sensors_Readings, &Temp) ;
			LCD_Clear();
			LCD_DisplayString( Sensors_Readings.pitchdeg_AC );
			LCD_Goto_xy(1,2);
			LCD_DisplayString( Sensors_Readings.rolldeg_AC);
			_delay_ms(500);
	}
	return 0;
}



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

/*
void Acc_setsoftware_offset (double x, double y, double z)
{
	{
	_xoffse = x;
	ACCS_OFSZ = y;
	ACCS_OFSZ = z;
	}
}
*/

/*--------------------------------------------------------------------------------*/

#define Accs_Range	5

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
