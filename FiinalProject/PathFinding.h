#pragma once
#include<AI.h>
#include <XEngine.h>




class PathFinding
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static  PathFinding& Get();

public:
	void Initialize();
	bool AstarDiagonal(int startX, int startY, int endX, int endY);
	inline std::vector<AI::GridBasedGraph::Node*> getPath() { return path; }
private:
	int startX;
	int startY;
	int endX;
	int endY;
	AI::GridBasedGraph graph;
	std::vector<AI::GridBasedGraph::Node*> path;
	std::list<AI::GridBasedGraph::Node*> openList;
	std::list<AI::GridBasedGraph::Node*> closedList;
};