 #pragma once
#include <AI.h>
#include <XEngine.h>

class DumbBehavior : public AI::SteeringBehavior
{
public:
	X::Math::Vector2 Calculate(AI::Agent& agent) override
	{
		auto agentToDestination = agent.destination - agent.position;
		if (X::Math::MagnitudeSqr(agentToDestination) <= 0.0f)
			return X::Math::Vector2::Zero();

		auto direction = X::Math::Normalize(agentToDestination);
		return direction * agent.maxSpeed;
	}
};

class SCV : public AI::Agent
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();
	void allBehavioursFlase();
	void SeekBehaviorTure();
	void ArriveBehaviorBehaviorTure();
	void FleeBehaviorTure();
	void wanderBehaviorTure();

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	DumbBehavior* mDumbBehavior = nullptr;
	SeekBehavior* mSeekBehavior = nullptr;
	ArriveBehavior* mArriveBehavior = nullptr;
	FleeBehavior* mFleeBehavior = nullptr;
	AI::Wanderbehavior* mWanderBehavior = nullptr;
	X::TextureId mTextureIds[16];
};