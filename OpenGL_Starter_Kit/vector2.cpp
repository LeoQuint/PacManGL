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

float vector2::Length()
{
	return sqrt((x*x) + (y*y));
}
