#include "Text.h"
#include <iostream>
#include <stdio.h>
#include <string>
Text::Text(char* my_text)
{
	list_ptr = glGenLists(1);
	glNewList(list_ptr, GL_COMPILE);
        Text::drawText(my_text);
    glEndList();
}


Text::~Text(void)
{
}

void Text::drawText(char* to_draw)
{
	glRasterPos3d(0.0,0.0,0);
    int p=0;
    while (to_draw[p]!='\0') {
		if(to_draw[p] == '\n') {
			glRasterPos3d(0.0,24.0,0);
			p++;
		} else {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, to_draw[p]);
			p++;
		}
    }
}

void Text::drawInt(int to_draw)
{
	std::string s =  std::to_string(to_draw);
	char* a = new char[s.size()+1];
	a[s.size()]=0;
	memcpy(a,s.c_str(),s.size());
	Text::drawText(a);
}

void Text::draw(void)
{
	glPushMatrix();
		glCallList(list_ptr);
	glPopMatrix();
}