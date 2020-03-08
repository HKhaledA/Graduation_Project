/*
 * Music_Player.c
 *
 * Created: 11/14/2018 8:43:30 PM
 *  Author: Hamdy
 */ 


#include "Music_Player.h"

typedef enum 
{
	NEXT=0x01,
	PREV=0x02,
	SELECTSONG=0x03,
	INC_VOL=0x04,
	DEC_VOL=0x05,
	SPE_VOL=0x06,
	

	
	SPPLAYBACKMODE=0x08,
	RESET=0x0C,
	PLAYBACK=0x0D,
	PAUSE=0x0E,
	
	STOP=0x16,
	
	DAC_ONLINE=0x1A,
	START_BYTE=0x7E,
	END_BYTE=0xEF,
	VER_INFO=0xFF,
	DummyData=0x00,
	
}DF_instructions;

uint8 defaultBuffer[]={START_BYTE , VER_INFO , SPE_VOL , DummyData , DummyData , DummyData , DummyData , END_BYTE};
	
uint8 dataBuffer[] ={START_BYTE , VER_INFO , SPE_VOL , DummyData , DummyData , DummyData , DummyData , END_BYTE};
void sendData()
{
	uint8 counter ;
	for(counter = 0 ; counter <8 ; counter ++ )
	{
		UART_SendByte(dataBuffer[counter]);
		dataBuffer[counter] = defaultBuffer[counter];
	}
	_delay_ms(100);
}

void DFPlayer_init(void)
{
	/* set Digital to Analog converter (DAC) online */
	dataBuffer[3] = DAC_ONLINE ; /*command to set DAC online */
	sendData(); /* send this command through uart to DFPlayer module*/
}
void DFPlayer_CMD_play(uint16 songNumber)
{
	dataBuffer[3] = SELECTSONG ; /* command to play song */
	if(songNumber < 256)
	{
		dataBuffer[6] = songNumber ;
	}
	else
	{
		dataBuffer[6] = (uint8)songNumber;
		dataBuffer[5] = (uint8)songNumber >> 8 ;
	}
	sendData();
}


void DFPlayer_CMD_setVolume(uint8 volume)
{
	if(volume > 30)
	{
		volume = 30;
	}
	dataBuffer[3] = SPE_VOL ;
	dataBuffer[6] = volume;
	sendData();
}
void DFPlayer_CMD_playContinues(uint8 songNumber)
{
	dataBuffer[3] = SPPLAYBACKMODE ; /* command to play song continue sly */
	if(songNumber < 256)
	{
		dataBuffer[6] = songNumber ;
	}
	else
	{
		dataBuffer[6] = (uint8)songNumber;
		dataBuffer[5] = (uint8)songNumber >> 8 ;
	}
	sendData();
}

void DFPlayer_CMD_pause(void)
{
	dataBuffer[3] = PAUSE ;
	sendData();
}

void DFPlayer_CMD_stop(void)
{
	dataBuffer[3] = STOP;
	sendData();
}
void DFPlayer_CMD_continue(void)
{
	dataBuffer[3] = PLAYBACK;
	sendData();
}
void DFPlayer_CMD_Reset(void)
{
	dataBuffer[3] = RESET;
	sendData();
}

void play_sound(uint16 Sound)
{
	DFPlayer_CMD_pause();
	DFPlayer_CMD_setVolume(30);
	DFPlayer_CMD_play(Sound);
}