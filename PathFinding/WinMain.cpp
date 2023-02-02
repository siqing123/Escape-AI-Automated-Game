#include<AI.h>
#include <XEngine.h>
#include"TileMap.h"
#include<ImGui/Inc/imgui.h>
#include <algorithm>

AI::GridBasedGraph graph;
TileMap tileMap;
using std::vector;
using std::string;
using std::list;

bool runBFS;
bool runDFS;
bool runDijkstra;
bool runAstarManhattan;
bool runAstarEuclidean;
bool runAstarDiagonal;

void resetBool()
{
	runBFS = false;
	runDFS = false;
	runDijkstra = false;
	runAstarManhattan = false;
}

X::Math::Vector2 GetPosition(int column, int row)
{
	return {column * 32.0f + 16.0f,row * 32.0f +16.0f};
}

X::Math::Vector2 GetPosition(AI::GridBasedGraph::Node* node)
{
	return GetPosition(node->column, node->row);
}

std::vector<AI::GridBasedGraph::Node*> path;
std::list<AI::GridBasedGraph::Node*> openList;
std::list<AI::GridBasedGraph::Node*> closedList;
int startX = 0, startY = 0;
int endX = 10, endY = 10;

bool compare(AI::GridBasedGraph::Node* a1, AI::GridBasedGraph::Node* a2) {
	return a1->g < a2->g;
}
 
bool RunBFS()
{
	bool foundPath = false;
	graph.Initialize(10, 10);
	// TODO: Reset everything ....
	graph.ResetSearchParams();
	path.clear();
	openList.clear();
	closedList.clear();
	// open and closed list, and the graph search params
	// Add start node to open list
	auto node = graph.GetNode(startX, startY);

	// TODO: Add search while loop here following the slides
	openList.push_back(node);

	node->opened = true;

	// While not done and there is more nodes in the open list
	while (!foundPath && !openList.empty())
	{
		//     0  1  2  3  4  5
		//  0 [_][_][_][_][_][_]
		//  1 [_][_][_][X][X][_]
		//  2 [_][_][_][X][_][_]

		if (openList.front()->column == endX && openList.front()->row == endY)//if the front element is the end node
		{
			foundPath = true;
		}
		else
		{
			for (int i = 0; i < 8; ++i) //check openlist front element push neighbors to openlist if neighbors is not in close or open list.
			{
				if (openList.front()->neighbors[i]
					&& !openList.front()->neighbors[i]->closed
					&& !openList.front()->neighbors[i]->opened
					&& tileMap.IsWalkable(openList.front()->neighbors[i]->column, openList.front()->neighbors[i]->row))// neighbors is not nullptr && neighbors not in openclose list
				{
					openList.push_back(openList.front()->neighbors[i]);
					openList.front()->neighbors[i]->parent = openList.front();
					openList.front()->neighbors[i]->opened = true;
				}
			}
		}

		closedList.push_back(openList.front());//then push front element to the closelist and remove it from openlist then track front element from openlist again
		openList.front()->closed = true;
		openList.pop_front();
	}

	// Check if we have a new path
	if (foundPath)
	{
		// Clear the old one!
		path.clear();

		// Beginning from the end node, trace back to it's parent one at a time
		auto node = graph.GetNode(endX, endY);
		while (node != nullptr)
		{
			path.push_back(node);
			node = node->parent;
		}

		// Once we recorded all the position from end to start, we need to reverse
		// them to get the correct order
		std::reverse(path.begin(), path.end());
	}
	return foundPath;	
}

bool RunDFS()
{
	bool foundPath = false;
	graph.Initialize(10, 10);
	// TODO: Reset everything ....
	graph.ResetSearchParams();
	path.clear();
	openList.clear();
	closedList.clear();
	// open and closed list, and the graph search params
	// Add start node to open list
	auto node = graph.GetNode(startX, startY);

	// TODO: Add search while loop here following the slides
	openList.push_back(node);

	node->opened = true;

	// While not done and there is more nodes in the open list
	while (!foundPath && !openList.empty())
	{
		//     0  1  2  3  4  5
		//  0 [_][_][_][_][_][_]
		//  1 [_][_][_][X][X][_]
		//  2 [_][_][_][X][_][_]
		auto node = openList.back();

		if (openList.back()->column == endX && openList.back()->row == endY)
		{
			foundPath = true;
		}
		else
		{
			for (int i = 0; i < 8; ++i) 
			{
				
				if (node->neighbors[i]
					&& !node->neighbors[i]->closed
					&& !node->neighbors[i]->opened
					&& tileMap.IsWalkable(node->neighbors[i]->column, node->neighbors[i]->row))// neighbors is not nullptr && neighbors not in openclose list
				{
					openList.push_front(node->neighbors[i]);
					node->neighbors[i]->parent = node;
					node->neighbors[i]->opened = true;
				}
			}
		}

		closedList.push_back(node);
		node->closed = true;
		openList.pop_back();
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

bool Dijkstra()
{
	float temp = 0.0f;
	list<AI::GridBasedGraph::Node*>::iterator it;
	bool foundPath = false;
	graph.Initialize(10, 10);
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
			for (int i = 0; i < 8; ++i)//look for 8 neighbors
			{
				if (node->neighbors[i] == nullptr || node->neighbors[i]->closed || !tileMap.IsWalkable(node->neighbors[i]->column, node->neighbors[i]->row))//skip the close one cause we dont run back
				{
					continue;
				}

				if (!node->neighbors[i]->opened)//if not in openlist
				{
					node->neighbors[i]->g = node->g + tileMap.GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);

					node->neighbors[i]->parent = node;
					node->neighbors[i]->opened = true;

					//add the neighbors to the openlist in order of small to large(g value)

					if (openList.empty())
					{
						openList.push_back(node->neighbors[i]);
					}
					else
					{
						it = openList.begin();
						//sort insertion
						while (it != openList.end() && (*it)->g < node->neighbors[i]->g)
						{
							++it;
						}
						openList.insert(it, node->neighbors[i]);
					}
				}
				else  //neighbor is in the openlist means neighbor has the g(cost from start to this neighbor) 
				{
					//temp: total cost from start to node to his neighbor
					temp = node->g + tileMap.GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);
					
					//if the new way is cheaper,replace the node in the openlist with this new way
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

bool AstarManhattan()
{
	float temp = 0.0f;
	list<AI::GridBasedGraph::Node*>::iterator it;
	bool foundPath = false;
	graph.Initialize(10, 10);
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
				if (node->neighbors[i] == nullptr || node->neighbors[i]->closed || !tileMap.IsWalkable(node->neighbors[i]->column, node->neighbors[i]->row))
					continue;

				if (!node->neighbors[i]->opened)
				{
					node->neighbors[i]->g = node->g + tileMap.GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);

					node->neighbors[i]->parent = node;
					node->neighbors[i]->opened = true;
					//add h valus to the neighbors
					node->neighbors[i]->h = tileMap.GetEstimatedDistanceManhattan(node->neighbors[i]->column,node->neighbors[i]->row,endX,endY);

					if (openList.empty())
					{
						openList.push_back(node->neighbors[i]);
					}
					else
					{
						it = openList.begin();
						//sort insertion  the only difference sort with g+h
						while (it != openList.end() && ( (*it)->g + (*it)->h ) < (node->neighbors[i]->g + node->neighbors[i]->h))
						{
							++it;
						}
						openList.insert(it, node->neighbors[i]);
					}
				}
				else  
				{
					temp = node->g + tileMap.GetTraversalCost(node->column,
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

bool AstarEuclidean()
{
	float temp = 0.0f;
	list<AI::GridBasedGraph::Node*>::iterator it;
	bool foundPath = false;
	graph.Initialize(10, 10);
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
				if (node->neighbors[i] == nullptr || node->neighbors[i]->closed || !tileMap.IsWalkable(node->neighbors[i]->column, node->neighbors[i]->row))
					continue;

				if (!node->neighbors[i]->opened)
				{
					node->neighbors[i]->g = node->g + tileMap.GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);

					node->neighbors[i]->parent = node;
					node->neighbors[i]->opened = true;
					//add h valus to the neighbors
					node->neighbors[i]->h = tileMap.GetEstimatedDistanceEuclidean(node->neighbors[i]->column, node->neighbors[i]->row, endX, endY);

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
					temp = node->g + tileMap.GetTraversalCost(node->column,
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

bool AstarDiagonal()
{
	float temp = 0.0f;
	list<AI::GridBasedGraph::Node*>::iterator it;
	bool foundPath = false;
	graph.Initialize(10, 10);
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
				if (node->neighbors[i] == nullptr || node->neighbors[i]->closed || !tileMap.IsWalkable(node->neighbors[i]->column, node->neighbors[i]->row))
					continue;

				if (!node->neighbors[i]->opened)
				{
					node->neighbors[i]->g = node->g + tileMap.GetTraversalCost(node->column,
						node->row,
						node->neighbors[i]->column,
						node->neighbors[i]->row);

					node->neighbors[i]->parent = node;
					node->neighbors[i]->opened = true;
					//add h valus to the neighbors
					node->neighbors[i]->h = tileMap.GetEstimatedDistanceDiagonal(node->neighbors[i]->column, node->neighbors[i]->row, endX, endY);

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
					temp = node->g + tileMap.GetTraversalCost(node->column,
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

void ShowPathingUI()
{
	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderInt("Start X", &startX, 0, tileMap.GetColumns()-1);
	ImGui::SliderInt("Start Y", &startY, 0, tileMap.GetRows()-1);
	ImGui::SliderInt("End X", &endX, 0, tileMap.GetColumns());
	ImGui::SliderInt("End Y", &endY, 0, tileMap.GetRows());

	X::DrawScreenCircle(X::Math::Vector2((startX * 32.0f) + 16.0f, (startY* 32.0f) + 16.0f), 12.0f, X::Colors::Blue);
	X::DrawScreenCircle(X::Math::Vector2((endX * 32.0f) + 16.0f, (endY * 32.0f) + 16.0f), 12.0f, X::Colors::Red);

	if (ImGui::Button("Run BFS"))
	{
		resetBool();
		runBFS = RunBFS();
	}
	if (ImGui::Button("Run DFS"))
	{
		resetBool();
		runDFS = RunDFS();
	}
	if (ImGui::Button("Run Dijkstra"))
	{
		resetBool();
		runDijkstra = Dijkstra();
	}
	if (ImGui::Button("Run AstarManhattan"))
	{
		resetBool();
		runAstarManhattan = AstarManhattan();
	}
	if (ImGui::Button("Run AstarEuclidean"))
	{
		resetBool();
		runAstarEuclidean = AstarEuclidean();
	}
	if (ImGui::Button("Run AstarDiagonal"))
	{
		resetBool();
		runAstarDiagonal = AstarDiagonal();
	}
	
	ImGui::End();
}

void ShowClosedList()
{
	for (auto iter = closedList.begin(); iter != closedList.end(); iter++)
	{
		if ((*iter)->parent)
		{
			X::DrawScreenLine(GetPosition((*iter)->parent), GetPosition(*iter), X::Colors::Red);
		}
	}
}

void ShowPath()
{
	for (auto iter = path.begin(); iter != path.end(); iter++)
	{
		if ((*iter)->parent)
		{
			X::DrawScreenLine(GetPosition((*iter)->parent), GetPosition(*iter), X::Colors::Cyan);
		}
	}
}


void GameInit()
{
	tileMap.LoadMap("map.txt");
	tileMap.LoadTiles("tile.txt");
}

bool GameLoop(float deltaTime)
{
	tileMap.Update();
	tileMap.Render();
	
	ShowPathingUI();
	ShowClosedList();
	ShowPath();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	//myMap.UnLoad();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}


