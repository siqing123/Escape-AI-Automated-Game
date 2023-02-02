#pragma once
#include"SteeringBehavior.h"

namespace AI
{
	class SteeringModule
	{
	public:
		SteeringModule(Agent& agent);

		template<class NewBehaviorType>
		NewBehaviorType* AddBehavior()
		{
			auto& newBehavior = mBehaviors.emplace_back(std::make_unique<NewBehaviorType>());
			return static_cast<NewBehaviorType*>(newBehavior.get());
		}

		void Purge();

		X::Math::Vector2 Calculate() const;

	private:
		Agent& mAgent;
		std::vector<std::unique_ptr<SteeringBehavior>> mBehaviors;
	};

}