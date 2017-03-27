#include "TitleScreen.h"
#include <windows.h>
#include <mmsystem.h>


TitleScreen::TitleScreen(void)
{
	material = 1;
	x = 0;
	y = 0;
	z = 0;
	list_ptr = glGenLists(1);
	glNewList(list_ptr, GL_COMPILE);
	glPushMatrix();
		Text::drawText("Hey its Pacman");
		glTranslatef(0, 1, 0);
		Text::drawText("For Game engine 2");
		glTranslatef(0, 1, 0);
		Text::drawText("Press \"i\" to Start!");
    glPopMatrix();
	glEndList();

	PlaySoundA((LPCSTR)"C:/Users/Leonard/Desktop/PacManOpenGL/Debug/pacman_beginning.wav", NULL, SND_FILENAME | SND_ASYNC);
}


TitleScreen::~TitleScreen(void)
{
}