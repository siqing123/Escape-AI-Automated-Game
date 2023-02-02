#include "Enemy.h"
#include"TileMap.h"
#include"enemyManager.h"
#include"Link.h"

const float Distance = 0.0f;

void Enemy::Load()
{
	mAliveTexture = X::LoadTexture("zelda.png");
	mDeadTexture = X::LoadTexture("zombie_dead.png");
	isAlive = true;
}


void Enemy::Render()
{
	if (IsAlive())
	{		
		X::DrawSprite(mAliveTexture, mPosition);
	}
}

void Enemy::Update(float deltaTime)
{
	if (X::Math::Distance(Link::Get().GetPosition(), mPosition) < 5.0f)
	{
		if (this->IsAlive())
		{
			Link::Get().getDamage(30);
			enemyManager::Get().addEnemyKill();
		}
		this->isAlive = false;	
	}
	//char buffer[20];
	//char buffer1[20];
	//char buffer2[20];
	//char buffer3[20];
	//int x = (int)Link::Get().getColumn();
	//int y = (int)Link::Get().getRow();
	//int mx = (int)mColumn;
	//int my = (int)mRow;
	//
	//_itoa_s(mx, buffer2, 10);
	//_itoa_s(my, buffer3, 10);
	//
	//X::DrawScreenText(buffer2,
	//	80.0f, // X
	//	20.0f, // Y
	//	24.0f, // font size,
	//	X::Colors::Blue);
	//X::DrawScreenText(buffer3,
	//	80.0f, // X
	//	40.0f, // Y
	//	24.0f, // font size,
	//	X::Colors::Blue);
}

void Enemy::setDistanceBetweenPlayer()
{
	mDistance = X::Math::Distance(Link::Get().GetPosition(), mPosition);
}

