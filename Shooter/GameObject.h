extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "SDL.h"
#include "GameState.h"
#include "Graphics.h"
#include <vector>
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"

#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	SDL_Rect Location;
	bool Destroyed;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);
	bool IsOutOfBounds(GameState* state);
	virtual std::vector<SDL_Rect> GetCollison();
	bool CheckCollision(GameObject* otherObject);
	std::vector<SDL_Rect> Collision;
	void SetPosition(int x, int y);
protected:
	virtual SDL_Surface* GetCurrentImage();
	virtual void Initialise(Graphics* graphics);
	void SetCollision(luabridge::LuaRef ref);
};

