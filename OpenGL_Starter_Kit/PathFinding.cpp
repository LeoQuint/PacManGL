#pragma once
#include "PathFinding.h"
#include <assert.h>  
//constructor
PathFinding::PathFinding()
{
	m_foundGoal = false;
}
//destructor
PathFinding::~PathFinding()
{
}
//Entry point to calculate a new A* path. Takes in the position from/to.
void PathFinding::FindPath(vector2 currentPos, vector2 targetPos)
{
	//Clear all our lists.
	for (int i = 0; i < m_openList.size(); i++)
	{
		delete m_openList[i];
	}
	m_openList.clear();
	for (int i = 0; i < m_visitedList.size(); i++)
	{
		delete m_visitedList[i];
	}
	m_visitedList.clear();
	for (int i = 0; i < m_path.size(); i++)
	{
		delete m_path[i];
	}
	m_path.clear();

	//init startNode
	Node start;
	start.x = currentPos.x;
	start.y = currentPos.y;
	//init endNode
	Node target;
	target.x = targetPos.x;
	target.y = targetPos.y;

	SetStartAndTarget(start, target);
	
	//Start the search.
	ContinueSearch();

}
//This returns the next vector2 position from the end of the list (the end is the starting location)
//and deletes that position (same as pop back).
vector2 PathFinding::NextPathPosition()
{
	vector2 nextPosition;
	nextPosition.x = m_path[m_path.size() - 1]->x;
	nextPosition.y = m_path[m_path.size() - 1]->y;
	//As long as we have more than 1 element, we erase it.
	//This means that if we keep querying NextPathPosition() until we reach the end, 
	//it will return the end position every time afterwards.
	if (m_path.size() > 1)
	{		
		m_path.erase(m_path.end() - 1);		
	}
	return nextPosition;
}
//Initializes the Node grid (this project as a 31X28 grid)
void PathFinding::InitGrid(std::vector<std::vector<Node*>> grid)
{
	this->m_grid = grid;	
}
//Initilizes the start and end nodes and adds the start node to the open list.
//this is where we start our search from.
void PathFinding::SetStartAndTarget(Node start, Node target)
{
	//Nodes have Walkable, x, y, and parents set.
	//We assume walkable is true since we are trying to path from/to it.
	m_StartNode = new Node(true, start.x, start.y, NULL);
	m_targetNode = new Node(true, target.x, target.y, NULL);


	m_StartNode->gCost = 0;
	//The heuristic we are using is simply the Manhattan Distance. 
	//(Its the absolute deltaX + deltaY from start node to end node)
	m_StartNode->hCost = m_StartNode->ManhattanDistance(m_targetNode);
	//finaly add to list.
	m_openList.push_back(m_StartNode);
}

void PathFinding::PathOpened(int x, int y, float newCost, Node * parent)
{
	
	if (!m_grid[x][y]->walkable) 
	{
		//printf("Tile not walkable skipping... \n");
		return;
	}
	
	int id = y * ROW_SIZE + x;
	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->id) 
		{
			//printf("Location previously visited.\n");
			return;
		}
	}

	//printf("Accessing grid at: %i %i\n", x, y);
	Node *child = new Node(m_grid[x][y]->walkable, x, y, parent);
	child->gCost = newCost;
	child->hCost = child->ManhattanDistance(m_targetNode);
	//printf("New h cost of: %f\n", child->hCost);
	if (child->hCost == 0)
	{
		printf("Zero hcost, we hit the target.\n");
	}
	for (int i = 0; i < m_openList.size(); i++)
	{
		//printf("Accessing open size / access %i%s%i\n", m_openList.size(), " / ",i);
		if (id == m_openList[i]->id) //if we already have this node in our open list.
		{
			float newF = child->fCost() /*+ newCost + m_openList[i]->hCost*/;

			if (m_openList[i]->fCost() > newF)	//check is this path has a lower fcost
												//if it does, replace it with the child
			{
				m_openList[i]->gCost = child->gCost/* + newCost*/;
				m_openList[i]->parent = child->parent;
				return;
			}
			else //worst fcost, simply remove the child of memory.
			{
				delete child;
				return;
			}
		}
	}
	//if we have yet to open this node, add to openlist.
	//printf("Adding new node to OpenList.");
	m_openList.push_back(child);

}
//this searches all the open nodes and returns the one with the smallest fCost.
Node * PathFinding::GetNextNode()
{
	float bestF = 99999.0f;//big number simply to set the first node's fCost as lowest from the start.
	int nodeIndex = -1;//The index of the best fCost node.
	Node *nextNode = NULL;
	//cycles through all the nodes and compares the current best fCost with fCost[i] from our list.
	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->fCost() < bestF)
		{
			bestF = m_openList[i]->fCost();
			nodeIndex = i;
		}
	}
	//Make sure we found a node or else big trouble.
	assert("Error value of nodeIndex is less than 0!" && nodeIndex >= 0);
	nextNode = m_openList[nodeIndex];
	//Once we select an open node to return, we add it to our list of visited.
	m_visitedList.push_back(nextNode);
	//Then remove from our visited list so we don't loop for ever.
	m_openList.erase(m_openList.begin() + nodeIndex);
	
	return nextNode;
}
//Each iteration of this function checks if:
//1- We have found our goal.
//2- The list of open Node is empty. -> if it is we ran out of nodes to look for a path.
//3- The next node with lowest fCost is the end node.
void PathFinding::ContinueSearch()
{
	while (!m_foundGoal)//while we haven't found our goal.
	{
		
		if (m_openList.empty())//if our list of open node is empty that means we cannot find a path (maybe blocked).
		{
			//I'v put an assert here since in pacman there should never be no possible paths.
			//Can be remove and changed to return a value to indicate no pathfinding possible.
			assert(!m_openList.empty() && "Error open list is empty. No paths could be found!");
			return;
		}

		Node *currentNode = GetNextNode();//Fetch the node with the lowest fCost from our list of open ones.

		if (currentNode->id == m_targetNode->id)//If this node is the same as our target we found our path.
		{
			//assign the parent of current node to our target node.
			//We could also simply use current node in the next loop but for readability i choosed this way.
			m_targetNode->parent = currentNode->parent;
			//iterator.
			Node *iteratorNode;
			//Simple for loop that on each pass assigns the x/y values of the node to a vector and adds it to a list.
			//We iterate by making the current node = to its parent and looping until the parent of our iterator is NULL (meaning we reached our starting point).
			for (iteratorNode = m_targetNode; iteratorNode != NULL; iteratorNode = iteratorNode->parent)
			{
				m_path.push_back(new vector2(iteratorNode->x, iteratorNode->y));//Our list of vectors is from [0] end to [end()] start.
			}
			//This is a small hack for pacman. I will be checking if our current position is different from the path's start point.
			m_currentPathFrom = vector2(this->m_StartNode->x, this->m_StartNode->y);

			printf("Founf path with %i nodes.\n", m_path.size());
			//Found goal + return is a bit redondant.
			m_foundGoal = true;
			return;
		}
		else //If the currentNode is NOT the endNode.
		{
			//Check all surrounding nodes. 
			//On this project the array is padded with unwalkable terrain around which will mark the nodes as visited. This make it so we don't need any array bound checks.
			//Check right
			PathOpened(currentNode->x + 1, currentNode->y, currentNode->gCost + 1, currentNode);
			//Check left
			PathOpened(currentNode->x - 1, currentNode->y, currentNode->gCost + 1, currentNode);
			//Check up
			PathOpened(currentNode->x, currentNode->y + 1, currentNode->gCost + 1, currentNode);
			//Check down
			PathOpened(currentNode->x, currentNode->y - 1, currentNode->gCost + 1, currentNode);

			for (int i = 0; i < m_openList.size(); i++)
			{
				//printf("CurrentNode id %i %i\n", currentNode->id, m_openList[i]->id);
				if (currentNode->id == m_openList[i]->id)
				{
					m_openList.erase(m_openList.begin() + i);
				}
			}
		}
	}

}
