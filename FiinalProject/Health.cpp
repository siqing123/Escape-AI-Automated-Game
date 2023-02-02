#include "Health.h"
#include"TileMap.h"
//#include"enemyManager.h"
#include"Link.h"

const float Distance = 0.0f;

void Health::Load()
{
	mAliveTexture = X::LoadTexture("carrot.png");
	isAlive = true;
}


void Health::Render()
{
	if (IsAlive())
	{
		X::DrawSprite(mAliveTexture, mPosition);
	}
}

void Health::Update(float deltaTime)
{
	if (X::Math::Distance(Link::Get().GetPosition(), mPosition) < 5.0f)
	{
		if (this->IsAlive() && Link::Get().getHP() < 50)
		{
			Link::Get().healing(30);
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

void Health::setDistanceBetweenPlayer()
{
	mDistance = X::Math::Distance(Link::Get().GetPosition(), mPosition);
}
