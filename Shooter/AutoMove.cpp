#include "AutoMove.h"

AutoMove::AutoMove(Resources* resources, luabridge::LuaRef ref, std::string initialState) : GameObject(resources, ref)
{
	State = initialState;

	Initialise(resources, ref);
}

AutoMove::~AutoMove()
{
}

void AutoMove::DoUpdate(GameState * state)
{
	if (Movement)
	{
		X = Location.x;
		Y = Location.y;

		Movement(this);

		Location.x = X;
		Location.y = Y;

		if (Frame < 0) Frame = Frames.size() - 1;
		if (Frame >= (int)Frames.size()) Frame = 0;
	}

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

void AutoMove::Initialise(Resources * resources, luabridge::LuaRef ref)
{
	Movement = GetFunction(ref, "movement");
	Count = 0;
}