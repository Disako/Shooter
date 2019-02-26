#include "AutoMove.h"
#include "Position.h"

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
		if (Frame >= (int)Frames.size()) Frame = 0;
	}
	else
	{
		Count++;
		if (Count >= FramesPerMove)
		{
			Count = 0;
			Location.x += SpeedX;
			Location.y += SpeedY;
		}
	}

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

void AutoMove::Initialise(Resources * resources, luabridge::LuaRef ref)
{
	auto movement = GetFunction(ref, "movement");
	if (movement.isNil())
	{
		Movement = nullptr;
	}
	else
	{
		Movement = movement;
	}
	Count = 0;
	SpeedX = GetInt(ref, "speedX", 0);
	SpeedY = GetInt(ref, "speedY", 0);
	FramesPerMove = GetInt(ref, "framesPerMove", 0);
}
