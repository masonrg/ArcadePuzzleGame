#include "Vector2Int.h"
#include <math.h>

Vector2Int::Vector2Int()
{
	x = 0;
	y = 0;
}

Vector2Int::Vector2Int(int x, int y)
{
	this->x = x;
	this->y = y;
}

float Vector2Int::magnitude() const
{
	return sqrt(sqrMagnitude());
}

float Vector2Int::sqrMagnitude() const
{
	return (float)(x * x + y * y);
}

float Vector2Int::distance(const Vector2Int & v)
{
	return (v - *this).magnitude();
}

float Vector2Int::sqrDistance(const Vector2Int & v)
{
	return (v - *this).sqrMagnitude();
}