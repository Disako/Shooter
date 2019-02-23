#include "AutoMove.h"
#include "Position.h"


AutoMove::AutoMove(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState) : GameObject(graphics, L, ref)
{
	State = initialState;

	Initialise(graphics, L, ref);
}

AutoMove::~AutoMove()
{
}

void AutoMove::DoUpdate(GameState * state)
{
	if (Movement)
	{
		Position position;
		position.X = Location.x;
		position.Y = Location.y;
		position.State = State;
		position.Frame = Frame;
		position.Count = Count;

		position = Movement(position);

		Location.x = position.X;
		Location.y = position.Y;
		State = position.State;
		Frame = position.Frame;
		Count = position.Count;
		if (Frame < 0) Frame = Frames.size() - 1;
		if (Frame >= Frames.size()) Frame = 0;
	}

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

void AutoMove::Initialise(Graphics * graphics, lua_State* L, luabridge::LuaRef ref)
{
	Movement = GetFunction(ref, "movement");
	Count = 0;
}
