#include "SCV.h"
#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

SCV scv;

void GameInit()
{
	scv.Load();
}

bool GameLoop(float deltaTime)
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		scv.destination.x = static_cast<float>(X::GetMouseScreenX());
		scv.destination.y = static_cast<float>(X::GetMouseScreenY());
	}

	if (X::IsKeyPressed(X::Keys::Q))
	{
		scv.allBehavioursFlase();
		scv.SeekBehaviorTure();
	}
	else if (X::IsKeyPressed(X::Keys::W))
	{
		scv.allBehavioursFlase();
		scv.ArriveBehaviorBehaviorTure();
	}
	else if (X::IsKeyPressed(X::Keys::E))
	{
		scv.allBehavioursFlase();
		scv.FleeBehaviorTure();
	}
	else if (X::IsKeyPressed(X::Keys::R))
	{
		scv.allBehavioursFlase();
		scv.wanderBehaviorTure();
	}

	scv.Update(deltaTime);
	scv.Render();

	X::DrawScreenDiamond(scv.destination, 10.0f, X::Colors::Red);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	scv.Unload();
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}