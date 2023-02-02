#pragma once
#include<XEngine.h>
#include<AI.h>
enum class linkState
{
	down,
	up,
	right,
	left
};

class Link
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static  Link& Get();

	void Load();
	void UnLoad();
	void Render();
	void Update(float deltaTime);
	inline int getColumn() { return mColumn; }
	inline int getRow() { return mRow; }
	inline int getHP() { return mHp; }
	void getDamage(int damage) { mHp = mHp - damage; if (mHp < 0) { mHp = 0; }}
	void healing(int heal) { mHp = mHp + heal; }
	void changeLinkState(X::Math::Vector2 direction);
	inline void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	inline void SetCurrentNode() { mColumn = (int)(mPosition.x / 32.0f); mRow = (int)(mPosition.y / 32.0f); }
	inline X::Math::Vector2& GetPosition() { return mPosition; }
	void ChangeState(int i);
	void setAllTargetPosition(std::vector<AI::GridBasedGraph::Node*> path);
	inline float getSpeed() { return mSpeed; }
	const X::Math::Vector2& GetTargetPosition(size_t index) const;
	size_t getTargetNode() { return targetNode; }
	void setTargetNode(size_t index) { targetNode = index; }
	int getSizeOfTargetPos() { return targetPositions.size(); }
private:
	int mHp;
	std::unique_ptr<AI::StateMachine<Link>> mStateMachine;
	std::vector<X::Math::Vector2> targetPositions;
	X::TextureId mTextureUp;
	X::TextureId mTextureDown;
	X::TextureId mTextureLeft;
	X::TextureId mTextureRight;
	X::TextureId temp;
	X::Math::Vector2 mPosition;
	float mSpeed;
	int mColumn;
	int mRow;
	size_t targetNode = 0;
	linkState mState = linkState::down;
	std::string mDialogue;
	std::string mHp_str;
};

