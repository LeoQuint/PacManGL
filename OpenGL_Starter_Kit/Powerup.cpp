#include "Powerup.h"


Powerup::Powerup(void)
{
	x = 0;
	y = 0;
	z = 0;
	material = 10;
	list_ptr = glGenLists(1);
	glNewList(list_ptr, GL_COMPILE);
    glPushMatrix();
		glutSolidSphere(0.25, 20, 20);
    glPopMatrix();
	glEndList();
}


Powerup::~Powerup(void)
{
}
