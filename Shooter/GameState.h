#pragma once
#include <map>
#include <vector>
#include "SDL.h"

class GameObject;

struct BackgroundSpawn
{
	int probability;
	std::string initialState;
};

class GameState
{
public:
	GameState();
	~GameState();

	const Uint8* Keys;
	std::vector<GameObject*> GameObjects;
	std::vector<GameObject*> BackgroundObjects;
	std::map<std::string, BackgroundSpawn> BackgroundSpawns;

	int ScreenWidth;
	int ScreenHeight;
	unsigned int Score = 0;
	bool GameOver = false;
};

