#pragma once
#include"Enemy.h"
#include"Health.h"
#include<XEngine.h>

class enemyManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static  enemyManager& Get();
	void Load();
	void Render();
	void generateEnemy();
	void generateHealth();
	void Update(float deltaTime);

	std::vector<Enemy*> GetEnemies() { return mEnemies; }
	std::vector<Health*> GetAllHeath() { return mHealth; }
	inline bool getEnmemyKill() { if (enemyKill == 5) { return false; } else { return true; } }
	inline void addEnemyKill() { enemyKill++; }
	void sortAllVector();
	void resetSortBool() { isSorted = false; }
private:
	std::vector<Enemy*> mEnemies;
	std::vector<Health*> mHealth;
	int enemyKill;
	std::string mDialogue;
	std::string enemyKill_str;
	bool isSorted;
};

