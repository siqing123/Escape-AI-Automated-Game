#include"Precompiled.h"
#include"GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	mNodes.clear();
	mNodes.resize(columns * rows);
	mColumns = columns;
	mRows = rows;

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			Node* node = GetNode(c, r);
			node->column = c;
			node->row = r;

			node->neighbors[0] = GetNode(c, r - 1);
			node->neighbors[1] = GetNode(c + 1, r - 1);
			node->neighbors[2] = GetNode(c + 1, r);
			node->neighbors[3] = GetNode(c + 1, r + 1);
			node->neighbors[4] = GetNode(c, r + 1);
			node->neighbors[5] = GetNode(c - 1, r + 1);
			node->neighbors[6] = GetNode(c - 1, r);
			node->neighbors[7] = GetNode(c - 1, r - 1);
		}
	}
}
void GridBasedGraph::ResetSearchParams()
{
	for (auto& node : mNodes)
	{
		node.g = 0.0f;
		node.h = 0.0f;
		node.parent = nullptr;
		node.opened = false;
		node.closed = false;
	}
}