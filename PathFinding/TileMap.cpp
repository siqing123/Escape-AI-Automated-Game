#include "TileMap.h"
#include<ImGui/Inc/imgui.h>
#include<algorithm>

TileMap::~TileMap()
{
	delete[] mMap;
	mMap = nullptr;
}

void TileMap::LoadMap(const char* fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName, "r");
	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows);
	delete []mMap;
	mMap = new int[mColumns * mRows];

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y, mColumns);
			mMap[index] = fgetc(file) - '0';//
		}
		fgetc(file);
	}
	fclose(file);

	
}

void TileMap::SaveMap(const char* fileName)
{

}

void TileMap::LoadTiles(const char* fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName, "r");
	int count = 0;
	fscanf_s(file, "Count: %d\n", &count);
	mTileSet.resize(count);
	for (int i = 0; i < count; ++i)//
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));
		//fscanf_s(file, "%s\n", buffer,5);
		mTileSet[i] = X::LoadTexture(buffer);//
	}

	fclose(file);
}

void TileMap::Resize(int columns, int rows)
{

	if (columns == mColumns && rows == mRows)//same
		return;

	if (columns <= 0 || rows <= 0)//cant proceed
		return;

	int* newMap = new int[columns * rows];//new map

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			const int index = GetIndex(c, r, columns);
			newMap[index] = 0;
		}	
	}
	mColumns = columns;
	mRows = rows;
	delete[] mMap;
	mMap = newMap;
}


void TileMap::UnLoad()
{

}

void TileMap::Update()
{
	//if (X::IsMousePressed(X::Mouse::LBUTTON))
	//{
	//	const int mouseX = X::GetMouseScreenX();
	//	const int mouseY = X::GetMouseScreenY();
	//	const int column = mouseX/mTileWidth;
	//	const int row = mouseY / mTileHeight;
	//	//todo  update this so its painting the tile of your choice
	//	const int index = GetIndex(column, row, mColumns);
	//	mMap[index] = mSelectedTile;
	//}
}

void TileMap::Render() const
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int mapIndex = GetIndex(x, y, mColumns);
			const int tileIndex = mMap[mapIndex];//
			const X::TextureId textureId = mTileSet[tileIndex];//
			X::Math::Vector2 position{ x * 32.0f,y * 32.0f };//
			X::DrawSprite(textureId, position, X::Pivot::TopLeft);
		}
	}
}

int TileMap::GetIndex(int column, int row,int columnCount)const
{

	return column + (row * columnCount);
	//row represent by y   column represent by x
}

bool TileMap::IsWalkable(int column,int row)
{
	
	int t = GetIndex(column, row, mColumns);
	
	switch ((int)mMap[t])
	{
	case 0:return true;
	
	case 1:return true;
		
	case 2:return false;
	
	case 3:return false;

	case 4:return false;

	case 5:return false;

	case 6:return false;

	default:return false;
	}

}

void TileMap::ShowDebugUI()
{
	ImGui::Begin("Map Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Load Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::OpenFileDialog(fileName, "Load Map", "Map Files(*.txt)\0*.txt"))
			LoadMap(fileName);
	}

	if (ImGui::Button("Save Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::OpenFileDialog(fileName, "Save Map", "Map Files(*.txt)\0*.txt"))
			SaveMap(fileName);
	}

	static int columns = mColumns;
	static int rows = mRows;

	ImGui::SliderInt("Columns", &columns, 5,50);
	ImGui::SliderInt("Rows", &rows, 5, 50);
	if (ImGui::Button("Resize Map"))
		Resize(columns, rows);

	for (int i = 0; i < (int)mTileSet.size(); ++i)
	{
		if (ImGui::ImageButton(X::GetSprite(mTileSet[i]), { (float)mTileWidth,(float)mTileHeight }))
			mSelectedTile = i;
		if (i + 1 < (int)mTileSet.size())
			ImGui::SameLine();
	}

	ImGui::End();
}

float TileMap::GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow)const
{
	//int fromTile = mMap[GetIndex(fromColumn, fromRow)];
	int toTile = mMap[GetIndex(toColumn, toRow, mColumns)];
	//toTile 0:glass  1:flower
	if (toTile == 0)
	{
		toTile += 1;
	}
	else
	{
		toTile = 1;
	}

	int difference = abs(toColumn + toRow - fromColumn - fromRow);

	if (difference == 1)
	{
		return (float)toTile;
	}
	else if (difference == 0 || difference == 2)
	{
		return (toTile * 1.4f);
	}
}

float TileMap::GetEstimatedDistanceManhattan(int currentColumn, int currentRow, int endColumn, int endRow) const
{
	int dx = abs(currentColumn - endColumn);
	int dy = abs(currentRow - endRow);
	return (dx+dy);
}

float TileMap::GetEstimatedDistanceEuclidean(int currentColumn, int currentRow, int endColumn, int endRow) const
{
	int dx = abs(currentColumn - endColumn);
	int dy = abs(currentRow - endRow);

	return sqrt(dx*dx + dy*dy);
}

float TileMap::GetEstimatedDistanceDiagonal(int currentColumn, int currentRow, int endColumn, int endRow) const
{
	int dx = abs(currentColumn - endColumn);
	int dy = abs(currentRow - endRow);

	return (dx+dy)+(sqrt(2)-2)* std::min(dx,dy);
}
