#include "TickTimer.h"

TickTimer::TickTimer(float delayTime, int fps)
{
	delayTicks = (int)(delayTime * fps);
}

bool TickTimer::Tick()
{
	return Tick(1.0f);
}

bool TickTimer::Tick(float delayScale)
{
	if (forcedTick)
	{
		currTickCount = 0;
		return true;
	}

	currTickCount += 1;
	if (currTickCount > ((int)(delayTicks * delayScale)))
	{
		currTickCount = 0;
		return true;
	}
	return false;
}

void TickTimer::ForceTick()
{
	forcedTick = true;
}

void TickTimer::ResetTick()
{
	currTickCount = 0;
}
