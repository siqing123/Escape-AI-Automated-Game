#pragma once

#include <AI.h>
#include <XEngine.h>

enum class MarioState
{
	MoveToMushroom,
	CollectMushroom,
	Idle
};

class Mario
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(MarioState nextState);
	void vectory() { isVectory = true; }

	void SetPosition(const X::Math::Vector2& pos) { mPosition = pos; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }

	void SetTargetMushroom(size_t index) { mTargetMushroom = index; }
	size_t GetTargetMushroom() const { return mTargetMushroom; }

	void SetPickMushroom(size_t index) { pickMushroom = index; }
	size_t GetPickMushroom() const { return pickMushroom; }
private:
	std::unique_ptr<AI::StateMachine<Mario>> mStateMachine;
	X::Math::Vector2 mPosition;
	X::TextureId mTextureId;
	size_t mTargetMushroom = 0;
	size_t pickMushroom = 0;

	X::TextureId mTextureIdVectory;
	bool isVectory;
};
