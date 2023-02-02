#include "MarioStates.h"

#include "MushroomWorld.h"

void MoveToMushroomState::Enter(Mario& mario)
{

}

void MoveToMushroomState::Update(Mario& mario, float deltaTime)
{
	//if   quanshi false 
	size_t target = mario.GetTargetMushroom();
	while (1)
	{
		if (!MushroomWorld::Get().IsMushroomCollected(target))
		{
			break;
		}
		else
		{
			target++;
		}
	}

	mario.SetPickMushroom(target);
	auto targetPos = MushroomWorld::Get().GetMushroomPosition(target);
	if (X::Math::Distance(mario.GetPosition(), targetPos) < 10.0f)
	{
		size_t nextTarget = target + 1;
		if (nextTarget >= MushroomWorld::Get().GetMushroomsLeft())
		{
			nextTarget = 0;
		}
		mario.SetTargetMushroom(nextTarget);

		mario.ChangeState(MarioState::CollectMushroom);
	}
	else
	{
		auto direction = X::Math::Normalize(targetPos - mario.GetPosition());
		auto velocity = direction * 300.0f;
		mario.SetPosition(mario.GetPosition() + (velocity * deltaTime));
	}
}

void MoveToMushroomState::Exit(Mario& mario)
{

}

void CollectMushroomState::Enter(Mario& mario)
{

}

void CollectMushroomState::Update(Mario& mario, float deltaTime)
{
	MushroomWorld::Get().CollectMushroom(mario.GetPickMushroom());
	if (MushroomWorld::Get().GetMushroomsLeft() > 0 )
	{
	   mario.ChangeState(MarioState::MoveToMushroom);
	}
	else
	{
		mario.ChangeState(MarioState::Idle);
	}
}

void CollectMushroomState::Exit(Mario& mario)
{

}

void IdleState::Enter(Mario& mario)
{

}

void IdleState::Update(Mario& mario, float deltaTime)
{
	mario.vectory();
}

void IdleState::Exit(Mario& mario)
{

}