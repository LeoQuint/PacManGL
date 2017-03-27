#pragma once
#include "glut_headers.h"
class MyDrawable
{
public:
	MyDrawable(void);
	~MyDrawable(void);
	virtual void draw(void);
	void setMaterial(int k);
	static void newMaterial(int k, float r, float g, float b);
	void setPoint(int x, int y);
	const static GLfloat mat_ambient[][24];
	const static GLfloat mat_diffuse[][4];
	const static GLfloat mat_specular[][4];
	const static GLfloat mat_shininess[][1];
	/*
	 *  First column:  emerald, jade, obsidian, pearl, ruby, turquoise	  0, 1, 2, 3, 4, 5
	 *  2nd column:  brass, bronze, chrome, copper, gold, silver		  6, 7, 8, 9, 10, 11
	 *  3rd column:  black, cyan, green, red, white, yellow plastic		  12, 13, 14, 15, 16, 17
	 *  4th column:  black, cyan, green, red, white, yellow rubber		  18, 19, 20, 21, 22, 23
	 */
protected:
	int list_ptr;
	int list_size;
	float x;
	float y;
	float z;
	int material;
};

