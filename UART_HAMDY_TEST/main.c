/*
 * main.c
 *
 *  Created on: Jun 17, 2019
 *      Author: Abdur
 */
#include "MICROCONIFG.h"
#include "STDTYPES.h"
#include "std_types.h"
#include "uart.h"

int main (void)
{
	UART_init();
	uint8 arr[]={'A', 'B', 'C', 'D', 'E'};
	while(1)
	{
		UART_SendArray(&arr, (uint8) 4);
		//		_delay_ms(2000);

	}
}


