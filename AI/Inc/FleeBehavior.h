#pragma once
#include"SteeringBehavior.h"
#include<algorithm>

class FleeBehavior : public AI::SteeringBehavior
{
public:
	FleeBehavior() {};
	X::Math::Vector2 Calculate(AI::Agent& agent) override
	{
		const float PanicDistanceSq = 100.0f * 100.0f;
		auto agentToDest = agent.destination - agent.position;
		if (X::Math::MagnitudeSqr(agentToDest) > PanicDistanceSq)
		{
			return X::Math::Vector2(0,0);
		}
		X::Math::Vector2 DesiredVelocity = X::Math::Normalize(agent.position - agent.destination) * agent.maxSpeed;
		return (DesiredVelocity - agent.velocity);
	}
};
