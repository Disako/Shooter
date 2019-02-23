#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <vector>
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "LuaLoadedObject.h"
#include "Graphics.h"
#include "GameState.h"

class Level :
	public LuaLoadedObject
{
public:
	Level(lua_State* L, std::string levelName);
	~Level();
	Level* DoUpdate(GameState* state, Graphics* graphics);
private:
	int Wait = 0;
	int Index = 0;
	std::vector<luabridge::LuaRef> Events;
	lua_State* L;
};

