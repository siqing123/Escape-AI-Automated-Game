#pragma once
#include<XEngine.h>
#include<AI.h>
class Health
{
public:
	void Load();
	void UnLoad();
	void Render();
	void Update(float deltaTime);
	int getColumn() const { return mColumn; }
	int getRow() const { return mRow; }
	void SetPosition(X::Math::Vector2& pos) { mPosition = pos; }
	X::Math::Vector2 GetPosition() const { return mPosition; }
	bool IsAlive() const { return isAlive; }
	void SetColumnsAndRows(int column, int row) { mColumn = column; mRow = row; }
	void setDistanceBetweenPlayer();
	float getDistanceBetweenPlayer() const { return mDistance; }

private:
	X::TextureId mAliveTexture;
	X::TextureId mDeadTexture;
	X::Math::Vector2 mPosition;
	float mDistance;
	bool isHitAnything;
	bool isAlive;
	int mColumn;
	int mRow;
};

