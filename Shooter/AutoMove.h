#pragma once
#include "GameObject.h"
class AutoMove :
	public GameObject
{
public:
	~AutoMove();
	void DoUpdate(GameState* state) override;
	std::string State;
protected:
	AutoMove(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState);
private:
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	luabridge::LuaRef Movement = nullptr;
};

