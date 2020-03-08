/*
 * uart.c
 *
 * Created: 11/14/2018 8:24:41 PM
 *  Author: Hamdy
 */ 


#include "uart.h"
#define  BAUD_RATE (9600.0)

	void UART_init(void)
	{
		
		uint16 UBRR_Value= ((F_CPU /(8.0 *BAUD_RATE ) ) - 1) +0.5;
		/* Set U2x " Double Speed Mode " */
		SET_BIT(UCSRA,U2X);
		
		/* Enable Rx , Tx */
		UCSRB |= (1<<TXEN) | (1<<RXEN);
		
		UCSRC |= (1<<URSEL) |(1<<UCSZ0) | (1<<UCSZ1);
		
		UBRRL = UBRR_Value & 0x00FF;
		UBRRH = UBRR_Value >>8;
	}
	
	void UART_SendByte(uint8 Data)
	{
		/* if Send Buffer is not empty wait until it being  empty */
		while (BIT_IS_CLEAR(UCSRA,UDRE))
		{
			
		}	
		UDR = Data;
		
	}
	
	void UART_SendArray(uint8 * Data , uint8 size)
	{
		uint8 i = 0;
		
		for(i=0;i<size;i++)
		{
			UART_SendByte(Data[i]);
		}
	}



uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    return UDR;		
}
