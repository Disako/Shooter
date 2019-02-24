#include "BackgroundObject.h"



BackgroundObject::BackgroundObject(Resources* resources, lua_State* L, std::string type, std::string initialState, bool fill)
	: BackgroundObject(resources, GetRef(L, type), initialState, fill)
{
}

BackgroundObject::BackgroundObject(Resources* resources, luabridge::LuaRef ref, std::string initialState, bool fill)
	: AutoMove(resources, ref, initialState)
{
	if (fill)
	{
		Location.x = Random(GetInt(ref, "fillX", 1, 0), GetInt(ref, "fillX", 2, 0));
		Location.y = Random(GetInt(ref, "fillY", 1, 0), GetInt(ref, "fillY", 2, 0));
	}
	else
	{
		Location.x = Random(GetInt(ref, "x", 1, 0), GetInt(ref, "x", 2, 0));
		Location.y = Random(GetInt(ref, "y", 1, 0), GetInt(ref, "y", 2, 0));
	}
}


BackgroundObject::~BackgroundObject()
{
}
