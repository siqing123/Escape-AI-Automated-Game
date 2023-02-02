#pragma once
#include"SteeringBehavior.h"
#include<algorithm>

class ArriveBehavior : public AI::SteeringBehavior
{
public:
	ArriveBehavior() {};
	X::Math::Vector2 Calculate(AI::Agent& agent) override
	{
		auto agentToDest = agent.destination - agent.position;
		auto distance = X::Math::Magnitude(agentToDest);

		if (distance > 0)
		{
			const float DecelTweaker = 0.3;
			float Deceleration = 5.0f;//can be changed
			//Speed ​​decreases with distance decrease but maxSpeed is the agent.maxSpeed
			float speed = distance / (DecelTweaker * Deceleration);
			speed = std::min(speed, agent.maxSpeed);
			X::Math::Vector2 DesiredVelocity = X::Math::Normalize(agentToDest) * speed;//agentToDest * speed / distance;

			//the force(vector2 velocity) change velocity to the desiredVelocity
			return (DesiredVelocity - agent.velocity);
		}
		//stop when arrived
		return X::Math::Vector2(0,0);
	}
};
