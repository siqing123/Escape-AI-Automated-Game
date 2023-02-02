#pragma once

#include <XEngine.h>

class MushroomWorld
{
public:
	static MushroomWorld& Get();

public:
	void Load();
	void Unload();

	void Render();

	void CollectMushroom(size_t index);

	const X::Math::Vector2& GetMushroomPosition(size_t index) const;
	bool IsMushroomCollected(size_t index) const;
	size_t GetMushroomsLeft() const;

private:
	std::vector<X::Math::Vector2> mMushroomPositions;
	std::vector<bool> mMushroomCollected;
	X::TextureId mTextureId;
	
};