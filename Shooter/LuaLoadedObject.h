#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include <map>

class LuaLoadedObject
{
public:
	~LuaLoadedObject();
protected:
	LuaLoadedObject();
	int GetInt(luabridge::LuaRef ref, std::string key, int defaultValue);
	int GetInt(luabridge::LuaRef ref, std::string key, int index, int defaultValue);
	int GetInt(luabridge::LuaRef ref, int index, std::string parent);
	bool GetBool(luabridge::LuaRef ref, std::string key, bool defaultValue);
	std::string GetString(luabridge::LuaRef ref, std::string key, std::string defaultValue);
	luabridge::LuaRef GetFunction(luabridge::LuaRef ref, std::string key);
	static luabridge::LuaRef GetRef(lua_State* L, std::string type);
	static std::map<std::string, luabridge::LuaRef*> Refs;
};

