#pragma once
#include "AutoMove.h"
class PlayerShot :
	public AutoMove
{
public:
	PlayerShot(Resources* resources, luabridge::LuaRef ref, std::string initialState);
	~PlayerShot();
	virtual void DoUpdate(GameState* state) override;

private:
	void Initialise(Resources* resources, luabridge::LuaRef ref);
	int Damage;
	bool Piercing;
};

