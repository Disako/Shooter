#include "UpgradeShip.h"



UpgradeShip::UpgradeShip(Resources* resources, lua_State* L, std::string type, std::string initialState)
	: UpgradeShip(resources, GetRef(L, type), initialState)
{
}

UpgradeShip::UpgradeShip(Resources* resources, luabridge::LuaRef ref, std::string initialState)
	: AutoMove(resources, ref, initialState)
{
}


UpgradeShip::~UpgradeShip()
{
}