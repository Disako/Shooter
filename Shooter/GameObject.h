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
	virtual ~GameObject();

	SDL_Rect Location;
	bool Destroyed;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);
	bool IsOutOfBounds(GameState* state);
	bool CheckCollision(GameObject* otherObject);
	std::vector<SDL_Rect> Collision;
	void SetPosition(int x, int y);
	SDL_Surface* Image;
protected:
	GameObject(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	virtual SDL_Surface* GetCurrentImage();
	int GetInt(luabridge::LuaRef ref, std::string key, int defaultValue);
	int GetInt(luabridge::LuaRef ref, std::string key, int index, int defaultValue);
	int GetInt(luabridge::LuaRef ref, int index, std::string parent);
	std::string GetString(luabridge::LuaRef ref, std::string key, std::string defaultValue);
	luabridge::LuaRef GetFunction(luabridge::LuaRef ref, std::string key);
	static luabridge::LuaRef GetRef(lua_State* L, std::string type);
private:
	void SetCollision(luabridge::LuaRef ref);
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
};

