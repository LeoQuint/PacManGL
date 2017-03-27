#pragma once
#include "mydrawable.h"
class Text :
	public MyDrawable
{
public:
	static void drawInt(int to_draw);
	static void drawText(char* to_draw);
	Text(char* my_text);
	~Text(void);
	void draw(void);
};

