#include "AutoMove.h"
#include "Position.h"


AutoMove::AutoMove(Graphics* graphics, std::tuple<lua_State*, luabridge::LuaRef> luaRef, std::string initialState) : GameObject(graphics, luaRef)
{
	State = initialState;

	Initialise(graphics, std::get<0>(luaRef), std::get<1>(luaRef));
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

		position = Movement(position);

		Location.x = position.X;
		Location.y = position.Y;
		State = position.State;
	}

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

void AutoMove::Initialise(Graphics * graphics, lua_State* L, luabridge::LuaRef ref)
{
	Movement = GetFunction(ref, "movement");
}
