#include "GameState.h"
#include "SDL.h"
#include "GameObject.h"
#include <vector>



GameState::GameState()
{
}


GameState::~GameState()
{
	for (unsigned int i = 0; i < GameObjects.size(); i++)
	{
		delete GameObjects[i];
	}
	GameObjects.clear();
}
