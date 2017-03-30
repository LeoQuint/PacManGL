#pragma once
#include "PathFinding.h"

PathFinding::PathFinding()
{
}

PathFinding::~PathFinding()
{
}

void PathFinding::FindPath(vector2 currentPos, vector2 targetPos)
{
}

vector2 PathFinding::NextPathPosition()
{
	return vector2();
}

void PathFinding::SetStartAndTarget(Node start, Node end)
{
}

void PathFinding::PathOpened(int x, int y, float newCost, Node * parent)
{
}

Node * PathFinding::GetNextNode()
{
	return nullptr;
}

void PathFinding::ContinuePath()
{
}
