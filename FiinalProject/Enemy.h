#pragma once
#include<XEngine.h>
#include<AI.h>
	class Enemy
{
public:
	void Load();
	void UnLoad();
	void Render();
	void Update(float deltaTime);
	inline int getColumn() const { return mColumn; }
	inline int getRow() const { return mRow; }
	inline void SetPosition(X::Math::Vector2& pos) { mPosition = pos; }	
	inline X::Math::Vector2 GetPosition() const { return mPosition; }
	bool IsAlive() const { return isAlive; }
	inline void SetColumnsAndRows(int column, int row) { mColumn = column; mRow = row;}
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


