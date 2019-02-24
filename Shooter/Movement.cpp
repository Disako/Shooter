#include "Movement.h"

Movement::Movement(luabridge::LuaRef ref, std::string key)
{
	Ref = ref[key];
	Key = key;
}

Movement::~Movement()
{
}

Position Movement::DoMovement(Position position)
{
	return Ref(position);
}
