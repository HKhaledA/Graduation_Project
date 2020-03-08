/*
 * ADXL345.c
 *
 * Created: 2/4/2017 7:04:57 PM
 *  Author: Eng.Hamdy Ahmed Hamdy
 *
 */ 

 
#include "ADXL345.h"
#include "lcd.h"

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



void Accelerometor_ReadAxis(ADXL345_Address EFF_Address ,volatile ADXL345_Data * Data_ptr)
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
