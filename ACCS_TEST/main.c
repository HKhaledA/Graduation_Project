/*
 * ADXL354.c
 *
 * Created: 9/3/2018 8:08:05 PM
 *  Author: Hamdy
 */ 

#include "LCD.h"
#include "i2c.h"
#include "std_types.h"
#include "ADXL345.h"

#define F_ADXL 400000UL

#define X_Angle_Accuracy 	 25
#define Y_Angle_Accuracy 	 25
#define Z_Angle_Accuracy 	 25


uint8 Word_index;

volatile ADXL345_Data Accs_Sensor_Reading;
volatile ADXL345_Data Live_Data;
ADXL345_Data Accs_Stored_Data[10]= {
										{ 250	, 7		, 30	},
										{ 240	, 67	, 29	},
										{ 245	, -22	, 27	},
								   };

u8  Compare_Accs_Data ( ADXL345_Data * Ptr_Accs_Readings, ADXL345_Data * Ptr_Acss_Stored_Data);


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
		if ( (Compare_Accs_Data(&Live_Data , &Accs_Stored_Data)))

				{
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
}

u8  Compare_Accs_Data ( ADXL345_Data * Ptr_Accs_Readings, ADXL345_Data * Ptr_Acss_Stored_Data)
{
	u8 i;
	Word_index=0;
	for (i=0; i<10; i++)
	{
		if  (
				( abs( (Ptr_Accs_Readings->X_Axis - Ptr_Acss_Stored_Data[i].X_Axis) ) <=  X_Angle_Accuracy )
			 && ( abs( (Ptr_Accs_Readings->Y_Axis - Ptr_Acss_Stored_Data[i].Y_Axis) ) <=  Y_Angle_Accuracy )
			 && ( abs( (Ptr_Accs_Readings->Z_Axis - Ptr_Acss_Stored_Data[i].Z_Axis) ) <=  Z_Angle_Accuracy )

/*
					( (Ptr_Accs_Readings->X_Axis - Ptr_Acss_Stored_Data[i].X_Axis ) >= - X_Angle_Accuracy )
				 && ( (Ptr_Accs_Readings->X_Axis - Ptr_Acss_Stored_Data[i].X_Axis ) <=   X_Angle_Accuracy )
				 && ( (Ptr_Accs_Readings->Y_Axis - Ptr_Acss_Stored_Data[i].Y_Axis ) >= - Y_Angle_Accuracy )
				 && ( (Ptr_Accs_Readings->Y_Axis - Ptr_Acss_Stored_Data[i].Y_Axis ) <=   Y_Angle_Accuracy )
				 && ( (Ptr_Accs_Readings->Z_Axis - Ptr_Acss_Stored_Data[i].Z_Axis ) >= - Z_Angle_Accuracy )
				 && ( (Ptr_Accs_Readings->Z_Axis - Ptr_Acss_Stored_Data[i].Z_Axis ) <=   Z_Angle_Accuracy )
*/


			)
		{
			Word_index= i + 1;
			return 1;
		}
	}
	return 0;
}
