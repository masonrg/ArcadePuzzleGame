#pragma once

#include <iostream>

class Direction
{
public:
	Direction();
	Direction(int angle);

	int clamp(int angle) const;
	int combine(int value) const;

	void set(int angle) { a = clamp(angle); }
	int get() const { return a; }

	//CASTING
	operator int() const { return a; }

	//PRESETS
	static Direction up() { return Direction(0); }
	static Direction down() { return Direction(180); }
	static Direction left() { return Direction(270); }
	static Direction right() { return Direction(90); }
	static Direction up_right() { return Direction(45); }
	static Direction down_right() { return Direction(135); }
	static Direction up_left() { return Direction(315); }
	static Direction down_left() { return Direction(225); }

	//ASSIGNMENT AND EQUALITY
	inline Direction& operator = (const Direction& v) { set(v.a); return *this; }
	inline Direction& operator = (const int& v) { set(v); return *this; }
	inline Direction& operator - (void) { set(a + 180); return *this; }
	inline bool operator == (const Direction& v) const { return a == v.a; }
	inline bool operator != (const Direction& v) const { return a != v.a; }

	//DIRECTION TO DIRECTION
	inline const Direction operator + (const Direction & v) const { return Direction(combine(v.a)); }
	inline const Direction operator - (const Direction & v) const { return -Direction(combine(v.a)); }

	//DIRECTION TO THIS
	inline Direction& operator += (const Direction & v) { a = combine(v.a); return *this; }
	inline Direction& operator -= (const Direction & v) { a = clamp(combine(v.a) + 180); return *this; }

	//SCALAR TO DIRECTION
	inline const Direction operator + (int v) const { return Direction(a + v); }
	inline const Direction operator - (int v) const { return Direction(a - v); }
	inline const Direction operator * (float v) const { return Direction((int)(a * v)); }

	//SCALAR TO THIS
	inline Direction& operator += (int v) { a = clamp(a + v); return *this; }
	inline Direction& operator -= (int v) { a = clamp(a + v); return *this; }
	inline Direction& operator *= (float v) { a = clamp((int)(a * v)); return *this; }

	//STREAM TO THIS
	friend std::ostream & operator <<(std::ostream& stream, const Direction& v) { return stream << "(" << v.a << " deg)"; }

private:
	int a;
};