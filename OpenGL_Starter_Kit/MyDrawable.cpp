#include "MyDrawable.h"
#include "glut_headers.h"

const GLfloat MyDrawable::mat_ambient[][24] = {
	{0.92, 0.81745, 0.81745,1.0},	//0 Dots -> pinkish
    {0.0, 0.0, 1.0,1.0},			//1 Walls/eyes -> Blue
    {0.05375, 0.05, 0.06625,1.0},	//2
    {0.25, 0.20725, 0.20725,1.0},	//3
    {1.0, 0.00, 0.00,1.0},			//4 blinky -> Red
    {0.0, 1.0, 1.0,1.0},			//5 inky -> cyan
    {1.0, 0.7, 0.8, 1.0},			//6 pinky -> pink
    {0.2125, 0.1275, 0.054, 1.0},	//7
    {0.25, 0.25, 0.25, 1.0},		//8
    {0.19125, 0.0735, 0.0225, 1.0},	//9
    {0.24725, 0.1995, 0.0745, 1.0},	//10
    {0.19225, 0.19225, 0.19, 1.0},	//11
    {0.02, 0.02, 0.02,1.0},			//12
    {0.0, 0.05, 0.05,1.0},			//13
    {0.0, 0.05, 0.0,1.0},			//14
    {1.0, 1.0, 0.0,1.0},			//15 pacman -> yellow
    {1.0, 0.7, 0.0,1.0},			//16 clyde -> Orange
    { 1, 1, 1,1.0}					//17 -> White
	};
const GLfloat MyDrawable::mat_diffuse[][4] = {
	{0.07568, 0.61424, 0.07568,1.0},
	{0.54, 0.89, 0.63,1.0},
	{0.18275, 0.17, 0.22525,1.0},
	{1, 0.829, 0.829,1.0},
	{0.61424, 0.04136, 0.04136, 1.0},
	{0.396, 0.74151, 0.69102,1.0},
	{0.780392, 0.568627, 0.113725, 1.0},
	{0.714, 0.4284, 0.18144, 1.0},
	{0.4, 0.4, 0.4, 1.0},
	{0.7038, 0.27048, 0.0828, 1.0},
	{0.75164, 0.60648, 0.22648, 1.0},
	{0.50754, 0.50754, 0.50754, 1.0},
	{0.01, 0.01, 0.01, 1.0},
	{0.4, 0.5, 0.5, 1.0},
	{ 0.4, 0.5, 0.4, 1.0},
	{ 0.5, 0.4, 0.4, 1.0},
	{0.5, 0.5, 0.5, 1.0},
	{0.5, 0.5, 0.4, 1.0}
};
const GLfloat MyDrawable::mat_specular[][4] = {
	{0.633,0.727811,0.633,1.0},
	{0.316228, 0.316228, 0.316228, 0.1},
	{0.332741, 0.328634, 0.346435,1.0},
	{0.296648, 0.296648, 0.296648,1.0},
	{0.727811, 0.626959, 0.626959,1.0},
	{0.297254, 0.30829, 0.306678,1.0},
	{0.992157, 0.941176, 0.807843, 1.0},
	{0.393548, 0.271906, 0.166721, 1.0},
	{0.774597, 0.774597, 0.774597, 1.0},
	{0.256777, 0.137622, 0.086014, 1.0},
	{0.628281, 0.555802, 0.366065, 1.0},
	{0.508273, 0.508273, 0.508273, 1.0},
	{0.4, 0.4, 0.4,1.0},
	{ 0.04, 0.7, 0.7,1.0},
	{0.04, 0.7, 0.04,1.0},
	{0.7, 0.04, 0.04,1.0},
	{0.7, 0.7, 0.7,1.0},
	{0.7, 0.7, 0.04,1.0}
};
const GLfloat MyDrawable::mat_shininess[][1] = {
	{0.6},{0.1},{0.3},{0.088}, {0.6},{0.1},
	{0.21794872},{ 0.2},{ 0.6},{ 0.1},{ 0.4},{ 0.4},
	{0.078125},{.078125},{.078125},{.078125},{.078125},{.078125},{.078125}
};

MyDrawable::MyDrawable(void)
{
}


MyDrawable::~MyDrawable(void)
{
}

void MyDrawable::draw(void)
{
	glPushMatrix();
		setMaterial(this->material);
		glTranslatef(x, y, 0);
		glCallList(list_ptr);
	glPopMatrix();
}
void MyDrawable::setMaterial (int k)
{
	GLfloat emission[4] = {0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient[k]);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[k]);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[k]);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess[k]);
}
void MyDrawable::newMaterial (int k, float r, float g, float b)
{
	GLfloat emission[4] = {r, g, b, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient[k]);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[k]);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[k]);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess[k]);
}

void MyDrawable::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
