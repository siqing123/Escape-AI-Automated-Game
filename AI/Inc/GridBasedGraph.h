#pragma once
namespace AI
{
	class GridBasedGraph
	{
	public:
		struct Node
		{
			std::array<Node*, 8>neighbors;
			int column = 0;
			int row = 0;

			Node* parent = nullptr;
			float g = 0.0f;
			float h = 0.0f;
			bool opened = false;
			bool closed = false;
		};

		void Initialize(int columns, int rows);
		void ResetSearchParams();

		Node* GetNode(int column, int row)
		{
			if (column < 0 ||
				column >= mColumns ||
				row < 0 ||
				row >= mRows)
			{
				return nullptr;
			}
			return &mNodes[column + (row * mColumns)];
		}

		const Node* GetNode(int column, int row) const
		{
			if (column < 0 ||
				column >= mColumns ||
				row < 0 ||
				row >= mRows)
			{
				return nullptr;
			}
			return &mNodes[column + (row * mColumns)];
		}

		int GetColumns()const { return mColumns; }
		int GetRows()const { return mRows; }
	private:
		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;
	};
}
