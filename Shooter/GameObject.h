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
#include "LuaLoadedObject.h"

#pragma once
class GameObject :
	public LuaLoadedObject
{
public:
	virtual ~GameObject();

	SDL_Rect Location;
	bool Destroyed;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);
	bool CheckCollision(GameObject* otherObject);
protected:
	GameObject(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	virtual SDL_Surface* GetCurrentImage();
	bool IsOutOfBounds(GameState* state);
private:
	SDL_Surface* Image;
	std::vector<SDL_Rect> Collision;
	void SetCollision(luabridge::LuaRef ref);
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
};

