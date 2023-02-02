#include "enemyManager.h"
#include "Link.h"
#include<string>
#include"TileMap.h"
namespace
{
	enemyManager* sInstance = nullptr;

	bool compareEnemy(const Enemy* a, const Enemy* b)
	{
		return a->getDistanceBetweenPlayer() < b->getDistanceBetweenPlayer();
	}

	bool compareHealth(const Health* a, const Health* b)
	{
		return a->getDistanceBetweenPlayer() < b->getDistanceBetweenPlayer();
	}
}

void enemyManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "EnemyManager already initialized");
	sInstance = new enemyManager();
}
void enemyManager::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
enemyManager& enemyManager::Get()
{
	XASSERT(sInstance != nullptr, "No EnemyManager created yet");
	return *sInstance;
}

void enemyManager::Load()
{
	isSorted = false;
	mDialogue = "Enemy kill: ";
	enemyKill = 0;
	generateEnemy();
	generateEnemy();
	generateEnemy();
	generateEnemy();
	generateEnemy();
	generateHealth();
	generateHealth();
	generateHealth();
	generateHealth();
}


void enemyManager::Update(float deltaTime)
{
	if (!mEnemies.empty())
	{
		for (auto enemy : mEnemies)
		{
			enemy->Update(deltaTime);
		}
	}

	if (!mHealth.empty())
	{
		for (auto health : mHealth)
		{
			health->Update(deltaTime);
		}
	}
}
void enemyManager::sortAllVector()
{
	if (!isSorted)
	{
		for (auto health : mHealth)
		{			
			health->setDistanceBetweenPlayer();
		}

		for (auto enemy : mEnemies)
		{
			enemy->setDistanceBetweenPlayer();
		}
		std::sort(mHealth.begin(), mHealth.end(), compareHealth);
		std::sort(mEnemies.begin(), mEnemies.end(), compareEnemy);
		isSorted = true;
	}
}
void enemyManager::Render()
{
	if (!mEnemies.empty())
	{
		for (auto enemy : mEnemies)
		{
			enemy->Render();
		}
	}
	if (!mHealth.empty())
	{
		for (auto health : mHealth)
		{
			health->Render();
		}
	}

	 enemyKill_str = std::to_string(enemyKill);
	X::DrawScreenText((mDialogue+enemyKill_str).c_str(),
		20.0f, // X
		20.0f, // Y
		24.0f, // font size,
		X::Colors::Red);
}

void enemyManager::generateEnemy()
{
	X::Math::Vector2 position;
	int column;
	int row;
	int index;
	int tileNumber;
	while (1)
	{
		 column = rand() % (TileMap::Get().getColumns());
		 row = rand() % (TileMap::Get().getRows());
		 index = TileMap::Get().GetIndex(column, row, TileMap::Get().getColumns());
		 tileNumber = TileMap::Get().getContentOfIndex(index);
		 if (tileNumber == 0|| tileNumber == 1)//glass flower
		 {
			 break;
		 }
	}
	Enemy* mEnemy = new Enemy();
	mEnemy->Load();
	mEnemy->SetColumnsAndRows(column, row);
	position = X::Math::Vector2((column * 32.0f), (row * 32.0f));
	mEnemy->SetPosition(position);
	mEnemies.emplace_back(mEnemy);
}

void enemyManager::generateHealth()
{

	X::Math::Vector2 position;
	int column;
	int row;
	int index;
	int tileNumber;
	while (1)
	{
		column = rand() % (TileMap::Get().getColumns());
		row = rand() % (TileMap::Get().getRows());
		index = TileMap::Get().GetIndex(column, row, TileMap::Get().getColumns());
		tileNumber = TileMap::Get().getContentOfIndex(index);
		if (tileNumber == 0 || tileNumber == 1)//glass flower
		{
			break;
		}
	}
	Health* health = new Health();
	health->Load();
	health->SetColumnsAndRows(column, row);
	position = X::Math::Vector2((column * 32.0f), (row * 32.0f));
	health->SetPosition(position);
	mHealth.emplace_back(health);
}
