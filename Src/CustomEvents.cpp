#include "CustomEvents.h"
#include <memory>

Uint32 TETRIS_EVENT_TYPE = (Uint32)-1;

void InitEvent()
{
	TETRIS_EVENT_TYPE = SDL_RegisterEvents(1);
}

void SendEvent(TetrisEvent eventCode)
{
	if (TETRIS_EVENT_TYPE != ((Uint32)-1))
	{
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = TETRIS_EVENT_TYPE;
		event.user.code = eventCode;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
	}
}