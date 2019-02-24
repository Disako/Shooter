#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "Position.h"

class Movement
{
public:
	Movement(luabridge::LuaRef ref, std::string key);
	~Movement();
	Position DoMovement(Position position);
private:
	luabridge::LuaRef Ref = nullptr;
	std::string Key;
};

