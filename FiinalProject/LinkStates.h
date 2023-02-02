#pragma once
#include <AI.h>
#include <XEngine.h>
#include"Link.h"

class MoveToEnemyState : public AI::State<Link>
{
public:
	void Enter(Link& mario) override;
	void Update(Link& mario, float deltaTime) override;
	void Exit(Link& mario) override;
};

class IdleState : public AI::State<Link>
{
public:
	void Enter(Link& mario) override;
	void Update(Link& mario, float deltaTime) override;
	void Exit(Link& mario) override;
};

class MoveToHealthState : public AI::State<Link>
{
public:
	void Enter(Link& mario) override;
	void Update(Link& mario, float deltaTime) override;
	void Exit(Link& mario) override;
};