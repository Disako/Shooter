#pragma once
#include "GameObject.h"
#include <functional>
#include "Position.h"

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
	std::function<Position(Position)> Movement = nullptr;
	bool hasMovementFunction;
	int Count = 0;
	int SpeedX, SpeedY, FramesPerMove;
};

