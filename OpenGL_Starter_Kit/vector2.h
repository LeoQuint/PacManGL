#pragma once
struct vector2
{
	float x;
	float y;
	vector2() : x(0), y(0) {}
	vector2(float _x, float _y): x(_x), y(_y) {}
	~vector2() {}

	vector2 vector2::operator+(const vector2& vec);
	vector2 vector2::operator-(const vector2& vec);
	float Length();
};