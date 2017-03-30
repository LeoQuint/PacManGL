#pragma once
#include "vector2.h"
#include <vector>
#include "Node.h"

class PathFinding
{
public:
	PathFinding(void);
	~PathFinding(void);

	void FindPath(vector2 currentPos, vector2 targetPos);
	vector2 NextPathPosition();
	void ClearOpenList() { m_openList.clear(); }
	void ClearVisitedList() { m_visitedList.clear(); }
	void ClearPath() { m_path.clear(); }

	bool m_initializedStartGoal;
	bool m_foundGoal;

private:

	void SetStartAndTarget(Node start, Node end);
	void PathOpened(int x, int y, float newCost, Node *parent);
	Node *GetNextNode();
	void ContinuePath();

	Node *m_StartNode;
	Node *m_targetNode;
	std::vector<Node*> m_openList;
	std::vector<Node*> m_visitedList;
	std::vector<vector2*> m_path;
};
