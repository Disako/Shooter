#pragma once
#include "AutoMove.h"
class BackgroundObject :
	public AutoMove
{
public:
	BackgroundObject(Resources* resources, lua_State* L, std::string type, std::string initialState);
	~BackgroundObject();
private:
	BackgroundObject(Resources* resources, luabridge::LuaRef ref, std::string initialState);
};

