#include "Ghost.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>  
#include "Node.h"


const int Ghost::mat = 3;

Ghost::Ghost(void)
{
	pathfinder = new PathFinding();
	
	x = 0;
	y = 0;
	z = 0;
	step = 1;
	m_direction = 1;
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

void Ghost::InitGid(std::vector<std::vector<Node*>> myGrid) 
{
	pathfinder->InitGrid(myGrid);
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
		printf("Moving...");
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
							
void Ghost::CalculatePath(int x, int y) 
{
	if (!this->IsGoingOut() && vector2(int(this->x), int(this->y)) != pathfinder->m_currentPathFrom)
	{
		pathfinder->ClearOpenList();
		pathfinder->ClearPath();
		pathfinder->ClearVisitedList();
		
		pathfinder->FindPath(vector2(int(this->GetX()), int(this->GetY())), vector2(x, y));
		//from		
		vector2 myPos = pathfinder->NextPathPosition();
		//to
		vector2 nextPos = pathfinder->NextPathPosition();
		//delta
		vector2 nextDir = nextPos - myPos;

			
		// 0 : down (gameboard[y+1][x])
		if (nextDir.y == 1)
		{
			printf("Next direction down: %i %i\n", nextDir.x, nextDir.y);
			m_direction = 0;
		}
		// 1 : up (gameboard[y-1][x])
		else if (nextDir.y == -1)
		{
			printf("Next direction up: %i %i\n", nextDir.x, nextDir.y);
			m_direction = 1;
		}
		// 2 : right (gameboard[y][x+1])
		else if (nextDir.x == 1)
		{
			printf("Next direction right: %i %i\n", nextDir.x, nextDir.y);
			m_direction = 2;
		}
		// 3: left (gameboard[y][x-1])
		else
		{
			printf("Next direction left: %i %i\n", nextDir.x, nextDir.y);
			m_direction = 3;
		}

		

	
		

	}
}
				//x y represent pacman's position.
void Ghost::chase(int x, int y, char gameboard[][28])
{
	printf("Chasing...");
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
		//Calculating a new target each intersection.
		if (rand() % 100 < wrong_prob)//Calculate if the AI will go in a diff direction.
		{
			printf("Going the wrong direction!! \n");
			m_direction = rand() % 4;
			std::vector<int> tryed;

			while (!goTo(m_direction, gameboard))
			{
				m_direction = rand() % 4;
			}
		}
		else 
		{
			CalculatePath(x, y);
			goTo(m_direction, gameboard);
		}
		break;
	default:
		goTo(m_direction, gameboard);
		break;
	}
	//try the best direction.
	//This is hacky AI if you want.
	/*
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
	*/
	

}


boolean Ghost::goTo(int dir, char gameboard[][28])
{
	printf("GOTO:\n");
	int x = 0;
	int y = 0;
	switch (dir)
	{
	case 0://down
		y = 1;
		break;
	case 1://up
		y = -1;
		break;
	case 2://right
		x = 1;
		break;
	case 3://left
		x = -1;
		break;
	}
	printf("Moving to tile: %c \n", gameboard[int(this->y + y)][int(this->x + x)]);
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

//wrap around
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

