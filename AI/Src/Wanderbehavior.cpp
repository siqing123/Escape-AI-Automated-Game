#include"Precompiled.h"
#include"WanderBehavior.h"
#include"Agent.h"
using namespace AI;

X::Math::Vector2 Wanderbehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 localTarget =  localWanderTarget;//(0,1)
	X::Math::Vector2 randomAmount = {wanderJitter,wanderJitter};//1.0f

	X::Math::Vector2 newTarget = localTarget+X::RandomVector2(-randomAmount, randomAmount);

	//get a vector2 with random direction and length is Radius(destination point on a circle)
	localWanderTarget = X::Math::Normalize(newTarget) * wanderRadius;
	//move the circle forward
	X::Math::Vector2 projectedTarget = localWanderTarget + X::Math::Vector2{ 0.0f,wanderDistance };

	//all above happened in local(agent is the centre)
	//then transform target into world space
	X::Math::Matrix3 worldTransform = agent.GetWorldTransform();
	X::Math::Vector2 worldWanderTarget = X::Math::TransformCoord(projectedTarget, worldTransform);

	X::Math::Vector2 circleCenter = X::Math::TransformCoord({ 0.0f,wanderDistance }, worldTransform);
	X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Green);
	X::DrawScreenCircle(circleCenter, wanderRadius, X::Colors::Cyan);
	X::DrawScreenCircle(worldWanderTarget, 2.0f, X::Colors::Red);


	//seek to wander target
	auto agentToTarget = worldWanderTarget - agent.position;
	auto desiredVelocity = X::Math::Normalize(agentToTarget) * agent.maxSpeed;
	return desiredVelocity - agent.velocity;
}