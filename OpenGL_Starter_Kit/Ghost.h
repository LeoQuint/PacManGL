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
	boolean update(int x, int y, char gameboard[][28]);
	void CalculatePath(int x, int y);
	boolean IsMoving() { return moving;  }
	boolean IsGoingOut() { return going_out; }
	boolean goTo(vector2 location, char gameboard[][28]);

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
	int dir;
	int my_material;
	float wrong_prob;
};

