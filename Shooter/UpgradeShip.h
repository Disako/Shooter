#pragma once
#include "AutoMove.h"
#include "PlayerInfo.h"
class UpgradeShip :
	public AutoMove
{
public:
	UpgradeShip(Resources* resources, lua_State* L, std::string type, std::string initialState);
	~UpgradeShip();
	std::function<PlayerInfo(PlayerInfo)> UpgradeAction = nullptr;
private:
	UpgradeShip(Resources* resources, luabridge::LuaRef ref, std::string initialState);
	void Initialise(luabridge::LuaRef ref);
};

