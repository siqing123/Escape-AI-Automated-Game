#include "Mario.h"
#include "MarioStates.h"

void Mario::Load()
{
	isVectory = false;
	mStateMachine = std::make_unique<AI::StateMachine<Mario>>(*this);
	mStateMachine->AddState<MoveToMushroomState>();	
	mStateMachine->AddState<CollectMushroomState>();
	mStateMachine->AddState<IdleState>();
	ChangeState(MarioState::MoveToMushroom);

	mTextureId = X::LoadTexture("mario_idle_01.png");
	mTextureIdVectory = X::LoadTexture("vectory.png");
}

void Mario::Unload()
{
	mTextureId = 0;
	mStateMachine.reset();
}

void Mario::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Mario::Render()
{
	if (isVectory)
	{
		X::Math::Vector2 pos = (X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f);
		X::DrawSprite(mTextureIdVectory, pos);
	}
	else
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Mario::ChangeState(MarioState nextState)
{
	mStateMachine->ChangeState((size_t)nextState);
	//mStateMachine->ChangeState(0);
}