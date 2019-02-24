#include "LuaLoadedObject.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include <sstream>


LuaLoadedObject::LuaLoadedObject()
{
}


LuaLoadedObject::~LuaLoadedObject()
{
}

luabridge::LuaRef LuaLoadedObject::GetRef(lua_State* L, std::string type)
{
	luabridge::LuaRef ref = luabridge::getGlobal(L, type.data());

	if (ref.isNil())
	{
		std::stringstream error;
		error << "Could not find object: " << type;
		throw std::runtime_error(error.str());
	}
	else if (!ref.isTable())
	{
		std::stringstream error;
		error << "Error loading " << type << ", expected a table";
		throw std::runtime_error(error.str());
	}

	return ref;
}

bool LuaLoadedObject::GetBool(luabridge::LuaRef ref, std::string key, bool defaultValue)
{
	if (ref[key].isNil())
	{
		return defaultValue;
	}
	else if (ref[key].isBool())
	{
		return ref[key];
	}
	else
	{
		std::stringstream error;
		error << "Invalid value for " << key << ", expects bool";
		throw std::runtime_error(error.str());
	}
}

int LuaLoadedObject::GetInt(luabridge::LuaRef ref, std::string key, int defaultValue)
{
	if (ref[key].isNil())
	{
		return defaultValue;
	}
	else if (ref[key].isNumber())
	{
		return ref[key];
	}
	else
	{
		std::stringstream error;
		error << "Invalid value for " << key << ", expects integer";
		throw std::runtime_error(error.str());
	}
}

int LuaLoadedObject::GetInt(luabridge::LuaRef ref, std::string key, int index, int defaultValue)
{
	if (ref[key].isNil())
	{
		return defaultValue;
	}
	else if (ref[key].isTable())
	{
		return GetInt(ref[key], index, key);
	}
	else
	{
		std::stringstream error;
		error << "Invalid value for " << key << ", expects list";
		throw std::runtime_error(error.str());
	}
}

int LuaLoadedObject::GetInt(luabridge::LuaRef ref, int index, std::string parent)
{
	if (index < 1)
	{
		throw std::runtime_error("Index must be greater than zero");
	}
	else if (ref.length() < index)
	{
		std::stringstream error;
		error << "Invalid value for " << parent << ", expects list of at least length " << index;
		throw std::runtime_error(error.str());
	}
	else
	{
		if (ref[index].isNumber())
		{
			return ref[index];
		}
		else
		{
			std::stringstream error;
			error << "Invalid value for " << parent << ", expects list of integers";
			throw std::runtime_error(error.str());
		}
	}
}

std::string LuaLoadedObject::GetString(luabridge::LuaRef ref, std::string key, std::string defaultValue)
{
	if (ref[key].isNil())
	{
		return defaultValue;
	}
	else if (ref[key].isString())
	{
		return ref[key];
	}
	else
	{
		std::stringstream error;
		error << "Invalid value for " << key << ", expects string";
		throw std::runtime_error(error.str());
	}
}

luabridge::LuaRef LuaLoadedObject::GetFunction(luabridge::LuaRef ref, std::string key)
{
	if (ref[key].isNil())
	{
		return nullptr;
	}
	else if (ref[key].isFunction())
	{
		return ref[key];
	}
	else
	{
		std::stringstream error;
		error << "Invalid value for " << key << ", expects function";
		throw std::runtime_error(error.str());
	}
}
