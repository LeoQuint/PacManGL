#pragma once
#include "MyDrawable.h"
class Wallmanager:
	public MyDrawable
{
public:
	Wallmanager(void);
	~Wallmanager(void);
	virtual void draw(int wall);
};

