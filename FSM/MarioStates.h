#pragma once

#include "Mario.h"
#include <AI.h>
#include <XEngine.h>

class MoveToMushroomState : public AI::State<Mario>
{
public:
	void Enter(Mario& mario) override;
	void Update(Mario& mario, float deltaTime) override;
	void Exit(Mario& mario) override;
};

class CollectMushroomState : public AI::State<Mario>
{
public:
	void Enter(Mario& mario) override;
	void Update(Mario& mario, float deltaTime) override;
	void Exit(Mario& mario) override;
};
class IdleState : public AI::State<Mario>
{
public:
	void Enter(Mario& mario) override;
	void Update(Mario& mario, float deltaTime) override;
	void Exit(Mario& mario) override;
};