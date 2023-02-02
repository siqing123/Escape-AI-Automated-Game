#include "PathFinding.h"
#include "TileMap.h"
using std::vector;
using std::string;
using std::list;

namespace
{
	PathFinding* sInstance = nullptr;
	const float TILE_SIZE = 32.0f;

	bool compare(AI::GridBasedGraph::Node* a1, AI::GridBasedGraph::Node* a2)
	{
		return a1->g < a2->g;
	}
}

void PathFinding::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "EnemyManager already initialized");
	sInstance = new PathFinding();
}
void PathFinding::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
PathFinding& PathFinding::Get()
{
	XASSERT(sInstance != nullptr, "No PathFinding created yet");
	return *sInstance;
}

void PathFinding::Initialize()
{
	graph.Initialize(TileMap::Get().getColumns(),TileMap::Get().getRows());
	path.clear();
}

bool PathFinding::AstarDiagonal(int startX, int startY,int endX,int endY)
{
	float temp = 0.0f;
	list<AI::GridBasedGraph::Node*>::iterator it;
	bool foundPath = false;
	graph.ResetSearchParams();
	path.clear();
	openList.clear();
	closedList.clear();
	auto node = graph.GetNode(startX, startY);
	openList.push_back(node);
	node->opened = true;
	node->g = 0.0f;

	while (!foundPath && !openList.empty())
	{
		auto node = openList.front();
		openList.pop_front();

		if (node->column == endX && node->row == endY)
		{
			foundPath = true;
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				if (node->neighbors[i] == nullptr || node->neighbors[i]->closed || !TileMap::Get().IsWalkable(node->neighbors[i]->column, node->neighbors[i]->row))
					continue;

				if (!node->neighbors[i]->opened)
				{
					node->neighbors[i]->g = node->g + TileMap::Get().GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);

					node->neighbors[i]->parent = node;
					node->neighbors[i]->opened = true;
					//add h valus to the neighbors
					node->neighbors[i]->h = TileMap::Get().GetEstimatedDistanceDiagonal(node->neighbors[i]->column, node->neighbors[i]->row, endX, endY);

					if (openList.empty())
					{
						openList.push_back(node->neighbors[i]);
					}
					else
					{
						it = openList.begin();
						//sort insertion  the only difference sort with g+h
						while (it != openList.end() && ((*it)->g + (*it)->h) < (node->neighbors[i]->g + node->neighbors[i]->h))
						{
							++it;
						}
						openList.insert(it, node->neighbors[i]);
					}
				}
				else
				{
					temp = node->g + TileMap::Get().GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);

					if (temp < node->neighbors[i]->g)
					{
						node->neighbors[i]->g = temp;
						node->neighbors[i]->parent = node;
						openList.sort(compare);
					}
				}
			}
		}
		closedList.push_back(node);
		node->closed = true;
	}

	if (foundPath)
	{
		path.clear();

		auto node = graph.GetNode(endX, endY);
		while (node != nullptr)
		{
			path.push_back(node);
			node = node->parent;
		}

		std::reverse(path.begin(), path.end());
	}
	return foundPath;
}
