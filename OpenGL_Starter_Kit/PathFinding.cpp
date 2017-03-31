#pragma once
#include "PathFinding.h"


PathFinding::PathFinding()
{
	m_initializedStartGoal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding()
{
}

void PathFinding::FindPath(vector2 currentPos, vector2 targetPos)
{
	
	if (!m_initializedStartGoal) 
	{
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
		m_initializedStartGoal = true;
	}
	if (m_initializedStartGoal) 
	{
		printf("Initialization complete\n");
		ContinuePath();
		printf("Finished computing, path is %i in length.\n", m_path.size());
	}
}

vector2 PathFinding::NextPathPosition(Ghost *ghost)
{
	int index = 1;
	vector2 nextPosition;
	nextPosition.x = m_path[m_path.size() - index]->x;
	nextPosition.y = m_path[m_path.size() - index]->y;

	
	vector2 distance = nextPosition - vector2(ghost->GetX(), ghost->GetY());
	if (index < m_path.size())
	{
		if (distance.Length() < 0.1)
		{
			m_path.erase(m_path.end() - index);
		}
	}
	return nextPosition;
}

void PathFinding::InitGrid(std::vector<std::vector<Node*>> grid)
{
	this->m_grid = grid;
	printf("Init: %d\n",grid[5][10]->walkable);
}

void PathFinding::SetStartAndTarget(Node start, Node target)
{
	m_StartNode = new Node(true, start.x, start.y, NULL);
	m_targetNode = new Node(true, target.x, target.y, &target);


	m_StartNode->gCost = 0;
	m_StartNode->hCost = m_StartNode->ManhattanDistance(m_targetNode);
	m_StartNode->parent = 0;

	m_openList.push_back(m_StartNode);
}

void PathFinding::PathOpened(int x, int y, float newCost, Node * parent)
{
	
	if (!m_grid[x][y]->walkable) 
	{
		printf("Tile not walkable skipping... \n");
		return;
	}
	
	int id = y * ROW_SIZE + x;
	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->id) 
		{
			printf("Location previously visited.\n");
			return;
		}
	}

	//printf("Accessing grid at: %i %i\n", x, y);
	Node *child = new Node(m_grid[x][y]->walkable, x, y, parent);
	child->gCost = newCost;
	child->hCost = child->ManhattanDistance(m_targetNode);
	printf("New h cost of: %f\n", child->hCost);
	if (child->hCost == 0)
	{
		printf("Zero hcost, we hit the target.\n");
	}
	for (int i = 0; i < m_openList.size(); i++)
	{
		printf("Accessing open size / access %i%s%i\n", m_openList.size(), " / ",i);
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
	printf("Adding new node to OpenList.");
	m_openList.push_back(child);

}

Node * PathFinding::GetNextNode()
{
	float bestF = 99999.0f;
	int nodeIndex = -1;
	Node *nextNode = NULL;

	for (int i = 0; i < m_openList.size(); i++)
	{
		//printf("Accessing open size / access %i%s%i\n", m_openList.size(), " / ", i);
		if (m_openList[i]->fCost() < bestF)
		{
			bestF = m_openList[i]->fCost();
			nodeIndex = i;
		}
	}
	if (nodeIndex >= 0)
	{
		//printf("Accessing open with cellIndex size / access %i%s%i\n", m_openList.size(), " / ", cellIndex);
		nextNode = m_openList[nodeIndex];
		m_visitedList.push_back(nextNode);
		m_openList.erase(m_openList.begin() + nodeIndex);
	}

	return nextNode;
}

void PathFinding::ContinuePath()
{
	while (!m_foundGoal)
	{
		//printf("List empty -> %d\n", m_openList.empty());
	
		if (m_openList.empty())
		{
			return;
		}
		//printf("ContinuePath ...\n");
		Node *currentNode = GetNextNode();
		if (currentNode->id == m_targetNode->id)//We got it.
		{
			printf("Founf path with id: %i\n", currentNode->id);
			m_targetNode->parent = currentNode->parent;

			Node *getPath;

			for (getPath = m_targetNode; getPath != NULL; getPath = getPath->parent)//creates the path of vectors
			{
				m_path.push_back(new vector2(getPath->x, getPath->y));
			}

			m_foundGoal = true;
			return;
		}
		else //we dont got it.
		{
			printf("Right x and y : %i%i\n", currentNode->x, currentNode->y);
			//right
			PathOpened(currentNode->x + 1, currentNode->y, currentNode->gCost + 1, currentNode);
			printf("Left x and y : %i%i\n", currentNode->x, currentNode->y);
			//left
			PathOpened(currentNode->x - 1, currentNode->y, currentNode->gCost + 1, currentNode);
			printf("Up x and y : %i%i\n", currentNode->x, currentNode->y);
			//up
			PathOpened(currentNode->x, currentNode->y + 1, currentNode->gCost + 1, currentNode);
			printf("Down x and y : %i%i\n", currentNode->x, currentNode->y);
			//down
			PathOpened(currentNode->x, currentNode->y - 1, currentNode->gCost + 1, currentNode);
			printf("End of 4 direction %i\n", m_openList.size());
			for (int i = 0; i < m_openList.size(); i++)
			{
				printf("CurrentNode id %i %i\n", currentNode->id, m_openList[i]->id);
				if (currentNode->id == m_openList[i]->id)
				{
					m_openList.erase(m_openList.begin() + i);
				}
			}
		}
	}

}
