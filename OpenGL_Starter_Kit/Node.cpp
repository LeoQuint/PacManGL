#include "Node.h"



Node::~Node(void)
{
}

bool Node::operator==(const Node &node)
{
	return (node.x == this->x && node.y == this->y);
}

bool Node::operator!=(const Node &node)
{
	return !(node.x == this->x && node.y == this->y);
}
