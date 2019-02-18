#pragma once
#include <vector>
#include "SDL.h"

class GameObject;

class GameState
{
public:
	GameState();
	~GameState();

	Uint8* Keys;
	std::vector<GameObject*> GameObjects;

	int ScreenWidth;
	int ScreenHeight;
};
