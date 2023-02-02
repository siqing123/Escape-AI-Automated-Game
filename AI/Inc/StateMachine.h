#pragma once

#include"State.h"
namespace AI
{
	template <class AgentType>
	class StateMachine
	{
	public:
		//using StateType = State<AgentType>;

		StateMachine(AgentType& agent)
			:mAgent(agent) {}

		template <class NewStateType>
		void AddState()
		{
			mStates.emplace_back(std::make_unique<NewStateType>());
		}

		void Purge()
		{
			mStates.clear();
		}

		void Update(float deltaTime)
		{
			mCurrentState->Update(mAgent,deltaTime);
		}

		void ChangeState(size_t index)
		{
			if (mCurrentState != nullptr)
				mCurrentState->Exit(mAgent);
			mCurrentState = mStates[index].get();
			mCurrentState -> Enter(mAgent);
		}

	private:
		AgentType& mAgent;

		//StateType* mCurrentState = nullptr;
		//std::vector<std::unique_ptr<StateType>> mStates;

		State<AgentType>* mCurrentState = nullptr;
		std::vector<std::unique_ptr<State<AgentType>>> mStates;
	};
}