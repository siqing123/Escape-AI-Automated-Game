#include"TileMap.h"
#include"PathFinding.h"
#include"Link.h"
#include"enemyManager.h"
#include<AI.h>
#include <XEngine.h>
#include<ImGui/Inc/imgui.h>

enum class GameState
{
	Start,
	GamePlay,
	Win,
	Lose
};
bool gameStart = false;
bool runAstarDiagonal = false;
float mTime = 0.0f;
static GameState mGame = GameState::Start;
X::Math::Vector2 GetPosition(int column, int row)
{
	return { column * 32.0f + 16.0f,row * 32.0f + 16.0f };
}
X::Math::Vector2 GetPosition(AI::GridBasedGraph::Node* node)
{
	return GetPosition(node->column, node->row);
}
X::Math::Vector2 GetCenterOfScreen()
{
	return { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
}
void ShowPathingUI()
{
	ImGui::Begin("VGP332", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Play"))
	{
		enemyManager::Get().sortAllVector();
		enemyManager::Get().resetSortBool();
		PathFinding::Get().AstarDiagonal(Link::Get().getColumn(), Link::Get().getRow(), enemyManager::Get().GetEnemies()[0]->getColumn(), enemyManager::Get().GetEnemies()[0]->getRow());
	}
	ImGui::End();
}
void ShowPath()
{
	auto path = PathFinding::Get().getPath();
	for (auto iter = path.begin(); iter != path.end(); iter++)
	{
		if ((*iter)->parent)
		{
			X::DrawScreenLine(GetPosition((*iter)->parent), GetPosition(*iter), X::Colors::Cyan);
		}
	}
}
void Start(float deltaTime)
{	
	X::TextureId StratPage = X::LoadTexture("1.png");
	X::TextureId StratPage2 = X::LoadTexture("2.png");
	
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		gameStart = true;
	}

	if (gameStart)
	{	
		if (mTime== 0.0f)
		{
			mTime = X::GetTime();
		}
		if (X::GetTime() - mTime > 2.0f)
		{
			X::DrawSprite(StratPage2, GetCenterOfScreen()); 
			if (X::GetTime() - mTime > 3.0f)
			{
				mTime == 0.0f;
				mGame = GameState::GamePlay;
			}
		}
		else
		{
			X::DrawSprite(StratPage, GetCenterOfScreen());
		}
	}
	else
	{
		X::DrawSprite(StratPage, GetCenterOfScreen());
	}
}
void Win(float deltaTime)
{
	X::TextureId StratPage3 = X::LoadTexture("win.jpg");
	X::DrawSprite(StratPage3, GetCenterOfScreen());
	if (gameStart)
	{
		mTime = X::GetTime();
		gameStart = false;
	}

	if (X::GetTime() - mTime > 6.0f)
	{	
		mTime = 0.0f;
		mGame = GameState::Start;
	}
}
void Playing(float deltaTime)
{
	if (enemyManager::Get().getEnmemyKill())
	{
		TileMap::Get().Update(deltaTime);
		TileMap::Get().Render();
		Link::Get().Update(deltaTime);
		Link::Get().Render();
		enemyManager::Get().Update(deltaTime);
		enemyManager::Get().Render();
		ShowPathingUI();
		//ShowPath();
	}
	else
	{
		mGame = GameState::Win;
	}
}

void GameInit()
{
	TileMap::StaticInitialize();
	TileMap::Get().LoadMap("Level.txt");
	TileMap::Get().LoadTextures("Tileset.txt");
	PathFinding::StaticInitialize();
	PathFinding::Get().Initialize();
	Link::StaticInitialize();
	Link::Get().Load();
	enemyManager::StaticInitialize();
	enemyManager::Get().Load();
}

bool GameLoop(float deltaTime)
{
	switch (mGame)
	{
	case GameState::Start:
		Start(deltaTime);
		break;
	case GameState::GamePlay:
		Playing(deltaTime);
		break;
	case GameState::Win:
		Win(deltaTime);
		break;
	case GameState::Lose:
		;
	default:
		break;
	}
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	
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