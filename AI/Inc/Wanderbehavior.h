#pragma once
#include"SteeringBehavior.h"
namespace AI
{
	struct Agent;

	class Wanderbehavior : public SteeringBehavior
	{
	public:	
		 X::Math::Vector2 Calculate(Agent& agent) override;	

		 X::Math::Vector2 localWanderTarget = X::Math::Vector2::YAxis();
		 float wanderDistance = 100.0f;
		 float wanderRadius = 10.0f;
		 float wanderJitter = 1.0f;
	};
}