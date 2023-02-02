#include "SCV.h"


void SCV::Load()
{
	// Set agent attributes
	radius = 16.0f;
	mass = 1.0f;
	maxSpeed = 200.0f;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<SeekBehavior>();
	mFleeBehavior = mSteeringModule->AddBehavior<FleeBehavior>();
	mArriveBehavior = mSteeringModule->AddBehavior<ArriveBehavior>();
	mDumbBehavior = mSteeringModule->AddBehavior<DumbBehavior>();
	mWanderBehavior = mSteeringModule->AddBehavior<AI::Wanderbehavior>();
	mWanderBehavior->wanderDistance = 100.0f;
	mWanderBehavior->wanderRadius = 200.0f;
	mWanderBehavior->wanderJitter = 10.0f;
	mTextureIds[0] = X::LoadTexture("scv_01.png");
	mTextureIds[1] = X::LoadTexture("scv_02.png");
	mTextureIds[2] = X::LoadTexture("scv_03.png");
	mTextureIds[3] = X::LoadTexture("scv_04.png");
	mTextureIds[4] = X::LoadTexture("scv_05.png");
	mTextureIds[5] = X::LoadTexture("scv_06.png");
	mTextureIds[6] = X::LoadTexture("scv_07.png");
	mTextureIds[7] = X::LoadTexture("scv_08.png");
	mTextureIds[8] = X::LoadTexture("scv_09.png");
	mTextureIds[9] = X::LoadTexture("scv_10.png");
	mTextureIds[10] = X::LoadTexture("scv_11.png");
	mTextureIds[11] = X::LoadTexture("scv_12.png");
	mTextureIds[12] = X::LoadTexture("scv_13.png");
	mTextureIds[13] = X::LoadTexture("scv_14.png");
	mTextureIds[14] = X::LoadTexture("scv_15.png");
	mTextureIds[15] = X::LoadTexture("scv_16.png");
}

void SCV::Unload()
{
	mSteeringModule.reset();
}

void SCV::Update(float deltaTime)
{
	

	auto force = mSteeringModule->Calculate();//
	velocity += force * deltaTime;
	position += velocity * deltaTime;

	// Adjust heading if we are moving
	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
		heading = X::Math::Normalize(velocity);
	//wrapping at the edge of the world
	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());
	if (position.x < 0.0f)
		position.x += screenWidth;
	if (position.x > screenWidth)
		position.x -= screenWidth;
	if (position.y < 0.0f)
		position.y += screenHeight;
	if (position.y > screenHeight)
		position.y -= screenHeight;
}

void SCV::Render()
{
	// Render SCV sprites
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	int frame = (int)(angle / X::Math::kTwoPi * 16.0f) % 16;
	X::DrawSprite(mTextureIds[frame], position);
}

void SCV::allBehavioursFlase()
{
	mSeekBehavior->SetActive(false);
	mArriveBehavior->SetActive(false);
	mFleeBehavior->SetActive(false);
	mWanderBehavior->SetActive(false);
}

void SCV::SeekBehaviorTure()
{
	mSeekBehavior->SetActive(true);
}

void SCV::ArriveBehaviorBehaviorTure()
{
	mArriveBehavior->SetActive(true);
}

void SCV::FleeBehaviorTure()
{
	mFleeBehavior->SetActive(true);
}

void SCV::wanderBehaviorTure()
{
	mWanderBehavior->SetActive(true);
}
