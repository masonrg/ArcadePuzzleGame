#pragma once

#include <iostream>

class Vector2Int
{
public:
	int x;
	int y;

	//CONSTRUCTORS
	Vector2Int();
	Vector2Int(int x, int y);

	//METHODS
	float magnitude() const;
	float sqrMagnitude() const;
	float distance(const Vector2Int & v);
	float sqrDistance(const Vector2Int & v);

	//ASSIGNMENT AND EQUALITY
	inline Vector2Int & operator = (const Vector2Int & v) { x = v.x; y = v.y; return *this; }
	inline Vector2Int & operator - (void) { x = -x; y = -y; return *this; }
	inline bool operator == (const Vector2Int & v) const { return (x == v.x) && (y == v.y); }
	inline bool operator != (const Vector2Int & v) const { return (x != v.x) || (y != v.y); }

	//VECTOR2 TO VECTOR2
	inline const Vector2Int operator + (const Vector2Int & v) const { return Vector2Int(x + v.x, y + v.y); }
	inline const Vector2Int operator - (const Vector2Int & v) const { return Vector2Int(x - v.x, y - v.y); }
	inline const Vector2Int operator * (const Vector2Int & v) const { return Vector2Int(x * v.x, y * v.y); }
	inline const Vector2Int operator / (const Vector2Int & v) const { return Vector2Int(x / v.x, y / v.y); }

	//VECTOR2 TO THIS
	inline Vector2Int & operator += (const Vector2Int & v) { x += v.x; y += v.y; return *this; }
	inline Vector2Int & operator -= (const Vector2Int & v) { x -= v.x; y -= v.y; return *this; }
	inline Vector2Int & operator *= (const Vector2Int & v) { x *= v.x; y *= v.y; return *this; }
	inline Vector2Int & operator /= (const Vector2Int & v) { x /= v.x; y /= v.y; return *this; }

	//SCALAR TO VECTOR2
	inline const Vector2Int operator + (int v) const { return Vector2Int(x + v, y + v); }
	inline const Vector2Int operator - (int v) const { return Vector2Int(x - v, y - v); }
	inline const Vector2Int operator * (int v) const { return Vector2Int(x * v, y * v); }
	inline const Vector2Int operator / (int v) const { return Vector2Int(x / v, y / v); }

	//SCALAR TO THIS
	inline Vector2Int & operator += (int v) { x += v; y += v; return *this; }
	inline Vector2Int & operator -= (int v) { x -= v; y -= v; return *this; }
	inline Vector2Int & operator *= (int v) { x *= v; y *= v; return *this; }
	inline Vector2Int & operator /= (int v) { x /= v; y /= v; return *this; }

	//STREAM TO THIS
	friend std::ostream & operator <<(std::ostream& stream, const Vector2Int& v) { return stream << "(" << v.x << "," << v.y << ")"; }
};