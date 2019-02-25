#pragma once
#include "GameObject.h"
#include <functional>

class AutoMove :
	public GameObject
{
public:
	~AutoMove();
	void DoUpdate(GameState* state) override;
	int Count = 0;
	std::string State;
	int X, Y;
protected:
	AutoMove(Resources* resources, luabridge::LuaRef ref, std::string initialState);
private:
	void Initialise(Resources* resources, luabridge::LuaRef ref);
	std::function<void(AutoMove*)> Movement = nullptr;
};

