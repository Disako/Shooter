#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "AutoMove.h"
#include <tuple>

class Enemy :
	public AutoMove
{
public:
	Enemy(Graphics* graphics, lua_State* L, std::string type, std::string initialState);
	~Enemy();
	int HP;
	void Damage(unsigned int damage);
	std::string State;
protected:
	SDL_Surface* GetCurrentImage() override;
private:
	Enemy(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState);
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
};

