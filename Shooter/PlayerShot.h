#pragma once
#include "AutoMove.h"
class PlayerShot :
	public AutoMove
{
public:
	PlayerShot(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState);
	~PlayerShot();
	virtual void DoUpdate(GameState* state) override;

private:
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	int Damage;
};

