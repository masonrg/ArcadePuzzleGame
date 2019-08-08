#include "Transform.h"
#include "../GameScreen.h"

Transform::Transform()
{
	position = { 0, 0 };
	scale = { 1.0f, 1.0f };
	rotation = Direction::up();
}

Transform::Transform(int x, int y)
{
	position = { x, y };
	scale = { 1.0f, 1.0f };
	rotation = Direction::up();
}

Transform::Transform(int x, int y, float xscl, float yscl)
{
	position = { x, y };
	scale = { xscl, yscl };
	rotation = Direction::up();
}

Transform::Transform(int x, int y, float xscl, float yscl, Direction orientation)
{
	position = { x, y };
	scale = { xscl, yscl };
	this->rotation = orientation;
}



Vector2Int Transform::GetCellPos() const
{
	return Vector2Int(GameScreen::toUnit(position.x), GameScreen::toUnit(position.y));
}

void Transform::SetCellPos(int x, int y)
{
	position.x = GameScreen::toPxl(x);
	position.y = GameScreen::toPxl(y);
}

void Transform::MoveByCells(int x, int y)
{
	position.x += GameScreen::toPxl(x);
	position.y += GameScreen::toPxl(y);
}
