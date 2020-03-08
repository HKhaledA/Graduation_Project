/*
 * Music_Player.h
 *
 * Created: 11/14/2018 8:43:40 PM
 *  Author: Hamdy
 */ 


#ifndef MUSIC_PLAYER_H_
#define MUSIC_PLAYER_H_


		#include "MICROCONIFG.h"
		#include "STDTYPES.h"
		#include "MACROS.h"
		#include "uart.h"
		
		void sendData();
		void DFPlayer_init(void);
		void DFPlayer_CMD_play(uint16 songNumber);
		void DFPlayer_CMD_setVolume(uint8 volume);
		void DFPlayer_CMD_playContinues(uint8 songNumber);
		void DFPlayer_CMD_pause(void);
		void DFPlayer_CMD_stop(void);
		void DFPlayer_CMD_continue(void);
		void DFPlayer_CMD_Reset(void);
		void play_sound(uint16 Sound);


#endif /* MUSIC_PLAYER_H_ */