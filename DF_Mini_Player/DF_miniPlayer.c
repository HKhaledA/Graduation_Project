/*
 * DF_miniPlayer.c
 *
 * Created: 11/14/2018 8:23:56 PM
 *  Author: Hamdy
 */ 


#include <avr/io.h>
#include "uart.h"
#include "Music_Player.h"

int main (void)
{
	UART_init();
	DFPlayer_init();
	uint8 i=1;
    while(1)
    {
        play_sound(i);
		_delay_ms(3000);
		i++;
		
		if(i>3)
		{
			i=1;
		}
			
    }
}
