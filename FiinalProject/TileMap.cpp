#include "TileMap.h"
#include<ImGui/Inc/imgui.h>
#include<algorithm>
namespace
{
	TileMap* sInstance = nullptr;
	const float TILE_SIZE = 32.0f;
}

void TileMap::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "EnemyManager already initialized");
	sInstance = new TileMap();
}
void TileMap::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
TileMap& TileMap::Get()
{
	XASSERT(sInstance != nullptr, "No EnemyManager created yet");
	return *sInstance;
}
void TileMap::NewMap()
{
}

void TileMap::LoadMap(std::filesystem::path fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows);

	mMap = new int[mColumns * mRows];

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y, mColumns);
			mMap[index] = fgetc(file) - '0';
		}
		fgetc(file);
	}
	fclose(file);
}

void TileMap::LoadTextures(std::filesystem::path fileName)//fileName为txt的图片名 存在Tileset01.txt
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	int count = 0;
	fscanf_s(file, "Count: %d\n", &count);
	mTileSet.resize(count);
	for (int i = 0; i < count; ++i)//加载图片种类 6种
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));//第四个参数 最多读取的字符数
		mTileSet[i] = X::LoadTexture(buffer);//mTiles 存入6种 X::TextureId
	}
	fclose(file);
}

void TileMap::SaveMap(std::filesystem::path fileName)
{
}
void TileMap::UnLoad()
{
	mTileSet.clear();
	mColumns = 0;
	mRows = 0;
	delete[] mMap;
	mMap = nullptr;
}
void TileMap::Render()
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
void TileMap::Update(float deltaTime)
{
}

bool TileMap::CheckCollision(const X::Math::LineSegment& lineSegment) const
{
	const int startX = static_cast<int>(lineSegment.from.x / TILE_SIZE);//地图上的第几个格子 每个格子加载不同图片
	const int startY = static_cast<int>(lineSegment.from.y / TILE_SIZE);
	const int endX = static_cast<int>(lineSegment.to.x / TILE_SIZE);
	const int endY = static_cast<int>(lineSegment.to.y / TILE_SIZE);
	//if out of bounds of the tile map 如果人物碰撞线跑出屏幕 
	if (startX < 0 || startX >= mColumns ||
		startY < 0 || startY >= mRows ||
		endX < 0 || endX >= mColumns ||
		endX < 0 || endY >= mRows)
	{
		return true;//返回碰撞
	}

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)//碰撞盒子长款24，地图格子32，碰撞线段长24 start比end大1 会检测人物面前两个格子的物体  
		{
			const int index = GetIndex(x, y, mColumns);
			if (mMap[index] > 1)//用数字大小代表不同图片类型 
			{
				return true;
			}
		}
	}
	return false;
}

X::Math::Rect TileMap::GetBound() const
{
	//Construct a rect and return it
	return{
		0.0f,//left
		0.0f,//top
		mColumns * TILE_SIZE,//right
		mRows * TILE_SIZE//bottom
	};
}


int TileMap::GetIndex(int column, int row, int columnCount)const
{
	return column + (row * columnCount);
	//row represent by y   column represent by x
}

bool TileMap::IsWalkable(int column, int row)
{

	int t = GetIndex(column, row, mColumns);

	switch (mMap[t])
	{
	case 0:return true;

	case 1:return true;

	case 2:return false;

	case 3:return false;

	case 4:return false;

	case 5:return false;

	case 6:return false;

	default:return true;
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

	ImGui::SliderInt("Columns", &columns, 5, 50);
	ImGui::SliderInt("Rows", &rows, 5, 50);

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
		toTile = 2;
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
	return (dx + dy);
}

float TileMap::GetEstimatedDistanceEuclidean(int currentColumn, int currentRow, int endColumn, int endRow) const
{
	int dx = abs(currentColumn - endColumn);
	int dy = abs(currentRow - endRow);

	return sqrt(dx * dx + dy * dy);
}

float TileMap::GetEstimatedDistanceDiagonal(int currentColumn, int currentRow, int endColumn, int endRow) const
{
	int dx = abs(currentColumn - endColumn);
	int dy = abs(currentRow - endRow);

	return (dx + dy) + (sqrt(2) - 2) * std::min(dx, dy);
}
