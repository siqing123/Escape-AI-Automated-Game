#include "MushroomWorld.h"

namespace
{
	constexpr size_t mushroomCount = 10;
}

MushroomWorld& MushroomWorld::Get()
{
	static MushroomWorld instance;
	return instance;
}

void MushroomWorld::Load()
{
	mMushroomCollected.resize(mushroomCount, false);

	for (size_t i = 0; i < mushroomCount; ++i)
		mMushroomPositions.push_back(X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f }));

	mTextureId = X::LoadTexture("mushroom.png");
}

void MushroomWorld::Unload()
{
	mTextureId = 0;
}

void MushroomWorld::Render()
{
    for (size_t i = 0; i < mMushroomPositions.size(); ++i)
    {
    	if (!mMushroomCollected[i])
    		X::DrawSprite(mTextureId, mMushroomPositions[i]);
    }	
}

void MushroomWorld::CollectMushroom(size_t index)
{
	mMushroomCollected[index] = true;
}

const X::Math::Vector2& MushroomWorld::GetMushroomPosition(size_t index) const
{
	return mMushroomPositions[index];
}

bool MushroomWorld::IsMushroomCollected(size_t index) const
{
	return mMushroomCollected[index];
}

size_t MushroomWorld::GetMushroomsLeft() const
{
	size_t left = 0;
	for (auto collected : mMushroomCollected)
	{
		if (!collected)
			left++;
	}
	return left;
}