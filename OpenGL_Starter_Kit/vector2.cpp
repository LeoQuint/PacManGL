#include "vector2.h"
#include <math.h>

vector2 vector2::operator+(const vector2 & vec)
{	
	return vector2(this->x + vec.x, this->y + vec.y);
}

vector2 vector2::operator-(const vector2 & vec)
{
	return vector2(this->x - vec.x, this->y - vec.y);
}

bool vector2::operator==(const vector2 & vec)
{
	if (&vec == NULL)
	{
		return false;
	}
	return (this->x == vec.x && this->y == vec.y);
}

bool vector2::operator!=(const vector2 & vec)
{
	if (&vec == NULL)
	{
		return true;
	}
	return !(this->x == vec.x && this->y == vec.y);
}

float vector2::Length()
{
	return sqrt((x*x) + (y*y));
}
