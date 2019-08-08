#include "Direction.h"
#include <algorithm>

Direction::Direction()
{
	set(0);
}

Direction::Direction(int angle)
{
	set(angle);
}

int Direction::clamp(int angle) const
{
	//ensure that angle is always positive and (0,360]
	int mod = angle % 360;
	return mod < 0 ? 360 + mod : mod;
}

int Direction::combine(int value) const
{
	//returns the angle between the two angles
	//the angle represents the smallest distance (there are 2 possible mid points between directions)
	int clampV = clamp(value);
	int min = std::min(a, clampV);
	int max = std::max(a, clampV);
	int result = min + (max - min) / 2;
	return max - min > 180 ? clamp(result + 180) : result;
}
