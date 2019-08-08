#pragma once

class TickTimer
{
public:
	TickTimer(float delayTime, int fps);

	bool Tick();
	bool Tick(float delayScale);

	void ForceTick();
	void ResetTick();

private:
	int currTickCount = 0;
	int delayTicks = 0;
	bool forcedTick = false;
};