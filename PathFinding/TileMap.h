#pragma once
#include<XEngine.h>

class TileMap
{
public:
	~TileMap();
	void LoadMap(const char* fileName);
	void SaveMap(const char* fileName);
	void LoadTiles(const char* fileName);
	void Resize(int columns, int rows);
	void UnLoad();
	void Render() const;
	void Update();
	int GetColumns()const { return mColumns; }
	int GetRows()const { return mRows; }
	int GetTileWidth()const { return mTileWidth; }
	int GetTileHeight()const { return mTileHeight; }
	bool IsWalkable(int column,int row);
	void ShowDebugUI();
	float GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow)const ;
	float GetEstimatedDistanceManhattan(int currentColumn,int currentRow,int endColumn,int endRow)const;
	float GetEstimatedDistanceEuclidean(int currentColumn, int currentRow, int endColumn, int endRow)const;
	float GetEstimatedDistanceDiagonal(int currentColumn, int currentRow, int endColumn, int endRow)const;
private:
	int GetIndex(int column, int row,int columnCount)const;

	int* mMap = nullptr;
	int mColumns = 0;
	int mRows = 0;

	std::vector<X::TextureId> mTileSet;//
	int mTileWidth = 0;
	int mTileHeight = 0;
	int mSelectedTile = 0;
};

