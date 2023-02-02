#include"Mario.h"
#include"MushroomWorld.h"
#include<AI.h>
#include <XEngine.h>
#include<ImGui/Inc/imgui.h>

Mario mario;

void GameInit()
{
	MushroomWorld::Get().Load();
	mario.Load();
}

bool GameLoop(float deltaTime)
{
	mario.Update(deltaTime);
	MushroomWorld::Get().Render();
	mario.Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	mario.Unload();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}


