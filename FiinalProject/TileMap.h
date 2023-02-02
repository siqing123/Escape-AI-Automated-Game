#pragma once
#include<XEngine.h>
class TileMap
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static  TileMap& Get();
public:
	void NewMap();
	void LoadMap(std::filesystem::path fileName);
	void LoadTextures(std::filesystem::path fileName);
	void SaveMap(std::filesystem::path fileName);
	void UnLoad();
	void Render();
	void Update(float deltaTime);
	bool CheckCollision(const X::Math::LineSegment& lineSegment)const;
	X::Math::Rect GetBound() const;
	inline int getColumns() { return mColumns; }
	inline int getRows() { return mRows; }

	bool IsWalkable(int column, int row);
	void ShowDebugUI();
	float GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow)const;
	float GetEstimatedDistanceManhattan(int currentColumn, int currentRow, int endColumn, int endRow)const;
	float GetEstimatedDistanceEuclidean(int currentColumn, int currentRow, int endColumn, int endRow)const;
	float GetEstimatedDistanceDiagonal(int currentColumn, int currentRow, int endColumn, int endRow)const;
	int GetIndex(int column, int row, int columnCounts)const;
	int getContentOfIndex(int index) { if (mMap) { return mMap[index]; } }
private:
	int* mMap = nullptr;
	int mColumns = 0;
	int mRows = 0;
	std::vector<X::TextureId> mTileSet;
	int mTileWidth = 0;
	int mTileHeight = 0;
	int mSelectedTile = 0;
};
