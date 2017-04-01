#pragma once
#include "mydrawable.h"
#include "vector2.h"
#include "PathFinding.h"
class Ghost :
	public MyDrawable
{
public:
	Ghost(void);
	~Ghost(void);
	void InitGid(std::vector<std::vector<Node*>>);
	//x,y positions of pacman are passed in.
	boolean update(int x, int y, char gameboard[][28]);
	void CalculatePath(int x, int y);
	boolean IsMoving() { return moving;  }
	boolean IsGoingOut() { return going_out; }

	vector2 nextDestination;
	boolean hasTarget = false;
	int mortal;
	virtual void makeMortal(void);
	const static int mat;
	void die(void);
protected:
	float step;
	boolean going_out;
	boolean moving;
	boolean goTo(int dir, char gameboard[][28]);


	PathFinding* pathfinder;
	std::vector<std::vector<Node*>> grid;
	
	virtual void chase(int x, int y, char gameboard[][28]);
	void wrap(void);
	//0 : down (gameboard[y+1][x]), 1 : up (gameboard[y-1][x]), 2 : right (gameboard[y][x+1]), 3: left (gameboard[y][x-1])
	int m_direction;
	int my_material;
	float wrong_prob;
};

