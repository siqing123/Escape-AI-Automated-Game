#pragma once
#include<XEngine.h>

namespace AI
{
	struct Agent;

	class SteeringBehavior
	{
	public:
		virtual ~SteeringBehavior() = default;

		virtual X::Math::Vector2 Calculate(Agent& agent) = 0;

		void SetWeight(float weight) { mWeight = weight; }
		float GetWeight()const { return mWeight; }

		void SetActive(bool active) { mActive = active; }
		bool IsActive() const { return mActive; }

	private:
		bool mActive = false;
		float mWeight = 1.0f;
	};

}