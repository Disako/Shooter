#include "BackgroundObject.h"



BackgroundObject::BackgroundObject(Resources* resources, lua_State* L, std::string type, std::string initialState)
	: BackgroundObject(resources, GetRef(L, type), initialState)
{
}

BackgroundObject::BackgroundObject(Resources* resources, luabridge::LuaRef ref, std::string initialState)
	: AutoMove(resources, ref, initialState)
{
	Location.x = Random(GetInt(ref, "x", 1, 0), GetInt(ref, "x", 2, 0));
	Location.y = Random(GetInt(ref, "y", 1, 0), GetInt(ref, "y", 2, 0));
}


BackgroundObject::~BackgroundObject()
{
}
