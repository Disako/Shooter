#pragma once
#include "AutoMove.h"
class UpgradeShip :
	public AutoMove
{
public:
	UpgradeShip(Resources* resources, lua_State* L, std::string type, std::string initialState);
	~UpgradeShip();
private:
	UpgradeShip(Resources* resources, luabridge::LuaRef ref, std::string initialState);
};

