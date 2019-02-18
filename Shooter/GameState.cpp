#include "GameState.h"
#include "SDL.h"
#include "GameObject.h"
#include <vector>



GameState::GameState()
{
	GameObjects = {};
}


GameState::~GameState()
{
	GameObjects = {};
}
