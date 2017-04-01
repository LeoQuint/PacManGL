#pragma once
struct vector2
{
	int x;
	int y;
	vector2() : x(0), y(0) {}
	vector2(int _x, int _y): x(_x), y(_y) {}
	~vector2() {}

	vector2 vector2::operator+(const vector2& vec);
	vector2 vector2::operator-(const vector2& vec);

	bool vector2::operator==(const vector2& vec);
	bool vector2::operator!=(const vector2& vec);

};