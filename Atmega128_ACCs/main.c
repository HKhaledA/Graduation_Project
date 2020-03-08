/*
 * ADXL354.c
 *
 * Created: 9/3/2018 8:08:05 PM
 *  Author: Hamdy
 */ 


#include "LCD.h"
#include "i2c.h"
#include "ADXL345.h"

#define F_ADXL 400000UL
volatile ADXL345_Data Live_Data;
int main(void)
{
	LCD_init();
	TWI_Init(I2C_PRESCALE1,I2C_intDisable,F_ADXL,0x01);
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	LCD_DisplayString("Testing LCD");
	_delay_ms(1000);
	
    while(1)
    {
		Accelerometor_ReadAxis(ADXL345_ALTERNATIVE_ADDRESS,&Live_Data);
        LCD_Clear();
		LCD_DisplayString("X=");
		LCD_DisplayInt((uint16) (Live_Data.X_Axis));
		LCD_DisplayString(" Y=");
		LCD_DisplayInt((uint16) (Live_Data.Y_Axis));
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("Z=");
		LCD_DisplayInt((uint16) (Live_Data.Z_Axis));
		_delay_ms(500);
		LCD_Clear();
		LCD_DisplayString("Updating ..");
		_delay_ms(500);
		
    }
}
