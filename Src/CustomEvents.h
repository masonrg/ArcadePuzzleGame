#pragma once

#include "SDL.h"

extern Uint32 TETRIS_EVENT_TYPE;

enum TetrisEvent : Sint32
{
	GameOver=0,
	Cleared1=1,
	Cleared2=2,
	Cleared3=3,
	Cleared4=4
};

extern void InitEvent();
extern void SendEvent(TetrisEvent eventCode);
