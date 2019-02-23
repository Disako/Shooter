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
	AutoMove(Graphics* graphics, std::tuple<lua_State*, luabridge::LuaRef> luaRef, std::string initialState);
private:
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	luabridge::LuaRef Movement = nullptr;
};

