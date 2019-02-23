#pragma once
#include "GameObject.h"
class AutoMove :
	public GameObject
{
public:
	~AutoMove();
	void DoUpdate(GameState* state) override;
protected:
	AutoMove(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState);
	std::string State;
private:
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	luabridge::LuaRef Movement = nullptr;
};

