/*
 * main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: Abdur
 */
#include <avr/io.h>
#include <avr/iom128.h>
#include "uart.h"


int main( void )
{
	unsigned char str[18] = "\n\rExplore Embedded";
	unsigned char strLenght = 18;
	unsigned char i = 0;

	UART_init();
	//USART_Transmit('S' );
	while(1)
	{
		UART_SendByte(str[i++] );
		if(i >= strLenght)
		i = 0;

	}
	return(0);
}
