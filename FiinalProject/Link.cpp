#include "Link.h"
#include"LinkStates.h"
#include<math.h>
namespace
{
	Link* sInstance = nullptr;
}

void Link::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "already initialized");
	sInstance = new Link();
}
void Link::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
Link& Link::Get()
{
	XASSERT(sInstance != nullptr, "No created yet");
	return *sInstance;
}

void Link::Load()
{
	mDialogue = "HP: ";
	mHp = 100;
	mRow = 3;
	mColumn = 3;
	mTextureDown = X::LoadTexture("front.png");
	mTextureUp = X::LoadTexture("up.png");
	mTextureRight = X::LoadTexture("right.png");
	mTextureLeft = X::LoadTexture("left.png");
	temp = X::LoadTexture("stone.png");
	mPosition = X::Math::Vector2((mColumn * 32.0f), (mRow * 32.0f));
	mSpeed = 100.0f;
	mStateMachine = std::make_unique<AI::StateMachine<Link>>(*this);
	mStateMachine->AddState<MoveToEnemyState>();
	mStateMachine->AddState<IdleState>();
	mStateMachine->AddState<MoveToHealthState>();
	ChangeState(0);
}

void Link::UnLoad()
{
}

void Link::Render()
{
	switch (mState)
	{
	case linkState::down:
		X::DrawSprite(mTextureDown, mPosition);
		break;
	case linkState::up:
		X::DrawSprite(mTextureUp, mPosition);
		break;
	case linkState::left:
		X::DrawSprite(mTextureLeft, mPosition);
		break;
	case linkState::right:
		X::DrawSprite(mTextureRight, mPosition);
		break;
	default:
		X::DrawSprite(temp, mPosition);
		break;
	}
	char buffer[20];
	mHp_str = std::to_string(Link::Get().getHP());
	
	X::DrawScreenText((mDialogue + mHp_str).c_str(),
			20.0f, // X
			50.0f, // Y
			24.0f, // font size,
			X::Colors::Blue);
}

void Link::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Link::changeLinkState(X::Math::Vector2 direction)
{
	float x = direction.x;
	float y = direction.y;
	float sin45 = sqrtf(2.0f) / 2;// 0.5f
	float squX = x * x;
	float squY = y * y;
	if (1.0f - x < 0.001f||1.0f == x)
	{
		//right
		mState = linkState::right;
	}
	else if (1.0f + x < -0.001f || -1.0f == x )
	{
		//left
		mState = linkState::left;
	}
	else if (1.0f - y < 0.001f || 1.0f == y)
	{
		//down
		mState = linkState::down;
	}
	else if (y == -1.0f || 1.0f + y < 0.001f)
	{
		//up
		mState = linkState::up;
	}
	else if (x < 1.0f && x > sin45)
	{
		//right
		mState = linkState::right;
	}
	else if (x > -1.0f && x < -sin45)
	{
		//left
		mState = linkState::left;
	}
	else if (x > -sin45 && x < sin45 && y < 0)
	{
		//up
		mState = linkState::up;
	}
	else if (x > -sin45 && x < sin45 && y > 0)
	{
		//down;
		mState = linkState::down;
	}
	
}

void Link::ChangeState(int i)
{
	mStateMachine->ChangeState(i);
}

void Link::setAllTargetPosition(std::vector<AI::GridBasedGraph::Node*> path)
{
	targetPositions.clear();
	X::Math::Vector2 targetPos;
	for (auto iter = path.begin(); iter != path.end(); iter++)
	{
		if ((*iter)->parent)//miss the first node,can not add the last node by is way parent is the node before itself but not after
		{
			targetPos = X::Math::Vector2(((*iter)->parent->column) * 32.0f , ((*iter)->parent->row) * 32.0f );
			targetPositions.emplace_back(targetPos);
		}
	}
	// add the last node
	targetPos = X::Math::Vector2((path.back()->column) * 32.0f, (path.back()->row) * 32.0f);
	targetPositions.emplace_back(targetPos);
}

const X::Math::Vector2& Link::GetTargetPosition(size_t index) const
{
	return targetPositions[index];
}


