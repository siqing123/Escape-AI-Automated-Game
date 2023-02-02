#pragma once
#include"SteeringBehavior.h"

	class SeekBehavior : public AI::SteeringBehavior
	{
	public:
		SeekBehavior() {};
		X::Math::Vector2 Calculate(AI::Agent& agent) override
		{
			X::Math::Vector2 agentToDest = agent.destination - agent.position;
			if (X::Math::MagnitudeSqr(agentToDest) < 1.0f)
			{
				return X::Math::Vector2();
				//
			}
			X::Math::Vector2 desiredVelocity = X::Math::Normalize(agentToDest) * agent.maxSpeed;
			//the force(vector2 velocity) change velocity to the desiredVelocity
			return desiredVelocity - agent.velocity;
		}
	};
