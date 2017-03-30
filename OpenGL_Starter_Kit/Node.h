#pragma once
#include <math.h>

#define ROW_SIZE 28

struct Node
{
public:
	Node() : parent(0) {}
	Node(bool _walkable, int _X, int _Y, Node *_parent): x(_X), y(_Y), parent(_parent), walkable(_walkable), id( (y * ROW_SIZE) + x), gCost(0), hCost(0) {}

	~Node(void);
	bool walkable;

	int x;
	int y;
	int id;
	Node *parent;

	float gCost;
	float hCost;
	

	bool Node::operator==(const Node& node);
	bool Node::operator!=(const Node& node);

	float fCost(){
		return gCost + hCost;	
	}
	float ManhattanDistance(Node *endNode)
	{
		float deltaX = (float)(fabs((float)this->x - (float)endNode->x));
		float deltaY = (float)(fabs((float)this->y - (float)endNode->y));
		return deltaX + deltaY;
	}

};

