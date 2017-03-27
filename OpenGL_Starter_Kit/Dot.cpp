#include "Dot.h"

//Delicious palettes
Dot::Dot(void)
{
	x = 0;
	y = 0;
	z = 0;
	material = 0;
	list_ptr = glGenLists(1);
	glNewList(list_ptr, GL_COMPILE);
    glPushMatrix(); 
					//Radius, slices, stacks
		glutSolidSphere(0.20, 20, 20);
    glPopMatrix();
	glEndList();
}


Dot::~Dot(void)
{
}
