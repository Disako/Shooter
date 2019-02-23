#pragma once
#include "GameObject.h"
class AutoMove :
	public GameObject
{
public:
	~AutoMove();
	void DoUpdate(GameState* state) override;
protected:
	AutoMove(Resources* resources, luabridge::LuaRef ref, std::string initialState);
	std::string State;
private:
	void Initialise(Resources* resources, luabridge::LuaRef ref);
	luabridge::LuaRef Movement = nullptr;
	int Count = 0;
};

