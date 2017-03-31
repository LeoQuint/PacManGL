#include "Ghost.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>  
#include "Node.h"

const int Ghost::mat = 3;

Ghost::Ghost(void)
{
	x = 0;
	y = 0;
	z = 0;
	step = 1;
	dir = rand() % 4;
	wrong_prob = 10;
	mortal = 0;
	material = mat;
	moving = true;
	going_out = true;
	list_ptr = glGenLists(1);
	glNewList(list_ptr, GL_COMPILE);
	glPushMatrix();

	glutSolidSphere(0.5, 20, 20);//top
	glTranslatef(0, 0.2, 0);
	glutSolidCube(0.8);//body
	glTranslatef(0, 0.5, 0);
	glutSolidSphere(0.2, 20, 20);//leg
	glTranslatef(-0.4, 0, 0);
	glutSolidSphere(0.2, 20, 20);//leg
	glTranslatef(0.8, 0, 0);
	glutSolidSphere(0.2, 20, 20);//leg

	glPopMatrix();
	glEndList();
}


Ghost::~Ghost(void)
{
}

boolean Ghost::update(int x, int y, char gameboard[][28])
{
	if (mortal > 0)//delay to be normal again.
	{
		mortal--;
		if (mortal == 0)
		{
			material = my_material;
		}
	}
	if (going_out && moving && this->y > 11)
	{
		if (this->x < 13)
		{
			this->x += step;
		}
		else if (this->x > 14)
		{
			this->x -= step;
		}
		else
		{
			this->y -= step;
		}
	}
	else if (going_out && moving) 
	{
		going_out = false;
	}
	else if (moving) 
	{
		if (this->x == x && this->y == y) 
		{
			if (mortal > 0) 
			{
				die();
				return false;
			}
			else 
			{//killed pacman
				return true;
			}
		}
		chase(x, y, gameboard);
		if (this->x == x && this->y == y) 
		{
			if (mortal > 0) 
			{
				die();
				return false;
			}
			else 
			{
				return true;
			}
		}
	}
	return false;
}
							


void Ghost::chase(int x, int y, char gameboard[][28])
{
	//a*
	//gcost = distance travelled
	//hcost = distance flying.
	//fcost = total
	
	int gCost = 0;
	int hCost = abs(this->x - x) + abs(this->y - y);
	int fCost = gCost + hCost;

	int deltaX = abs(this->x - x);
	int deltaY = abs(this->y - y);

	int mx = this->x;
	int my = this->y;
	bool isWrong = false;

	switch (gameboard[my][mx])
	{
	case 'i':
	case 'f':
	case 'w':
		//printf("Intersection!! \n");
		
		if (rand() % 100 < wrong_prob)
		{
			isWrong = true;
		}
		break;	
	default:
		//printf("not an intersection %i%i%c\n",this->y,this->x, gameboard[my][mx]);
		goTo(dir, gameboard);
		return;
		break;
	}
	//try the best direction.
	if (!isWrong) 
	{
		if (deltaX > deltaY)
		{
			if (this->x > x)
			{
				dir = 0;
			}
			else
			{
				dir = 2;
			}
		}
		else
		{
			if (this->y > y)
			{
				dir = 1;
			}
			else
			{
				dir = 3;
			}
		}
	}
	else 
	{
		if (deltaX < deltaY)
		{
			if (this->x < x)
			{
				dir = 0;
			}
			else
			{
				dir = 2;
			}
		}
		else
		{
			if (this->y < y)
			{
				dir = 1;
			}
			else
			{
				dir = 3;
			}
		}
	}
	

	std::vector<int> tryed;
	
	while (!goTo(dir, gameboard))
	{
		tryed.push_back(dir);
		switch (dir) 
		{
		case 0:
			if (this->y > y && tryed.end() == std::find(tryed.begin(), tryed.end(), 1))
			{
				dir = 1;
			}
			else if( tryed.end() == std::find(tryed.begin(), tryed.end(), 3))
			{
				dir = 3;
			}
			else 
			{
				dir = 2;
			}
			break;
		case 1:
			if (this->x > x  && tryed.end() == std::find(tryed.begin(), tryed.end(), 0))
			{
				dir = 0;
			}
			else if(tryed.end() == std::find(tryed.begin(), tryed.end(), 2))
			{
				dir = 2;
			}
			else 
			{
				dir = 3;
			}
			break;
		case 2:
			if (this->y > y && tryed.end() == std::find(tryed.begin(), tryed.end(), 1))
			{
				dir = 1;
			}
			else if(tryed.end() == std::find(tryed.begin(), tryed.end(), 3))
			{
				dir = 3;
			}
			else 
			{
				dir = 0;
			}
			break;
		case 3:
			if (this->x > x && tryed.end() == std::find(tryed.begin(), tryed.end(), 0))
			{
				dir = 0;
			}
			else if(tryed.end() == std::find(tryed.begin(), tryed.end(), 2))
			{
				dir = 2;
			}
			else 
			{
				dir = 1;
			}

			break;
		}
	}
	
	
}
boolean Ghost::goTo(int dir, char gameboard[][28])
{
	int x = 0;
	int y = 0;
	switch (dir)
	{
	case 0:
		x -= step;
		break;
	case 1:
		y -= step;
		break;
	case 2:
		x = step;
		break;
	case 3:
		y = step;
		break;
	}
	switch (gameboard[int(this->y + y)][int(this->x + x)])
	{
	case '0':
	case 'i':
	case 'd':
	case 'f':
	case 'u':
	case 'w':

		this->y += y;
		this->x += x;
		return true;
	case '9':
		wrap();
	default:
		return false;
		break;
	}
}
void Ghost::wrap(void)
{
	setPoint(abs(x - 27), y);
}

void Ghost::makeMortal(void)
{
	mortal = 40;
	material = 0;
}

void Ghost::die(void)
{
	mortal = 0;
	x = 13;
	y = 14;
	going_out = true;
	material = my_material;
}

