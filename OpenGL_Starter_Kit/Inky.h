#pragma once
#include "ghost.h"
class Inky :
	public Ghost
{
public:
	Inky(void);
	~Inky(void);
	const static int mat;
	int dir;
};

