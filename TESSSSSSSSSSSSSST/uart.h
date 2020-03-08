/*
 * uart.h
 *
 * Created: 11/14/2018 8:24:49 PM
 *  Author: Hamdy
 */ 


#ifndef UART_H_
#define UART_H_

	#include "STDTYPES.h"
	#include "MICROCONIFG.h"
	#include "MACROS.h"
	
	
	
	void UART_init(void);
	void UART_SendByte(uint8 Data);
	void UART_SendArray(uint8 * Data , uint8 size);




#endif /* UART_H_ */