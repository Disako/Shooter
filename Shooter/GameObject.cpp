extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "GameObject.h"
#include "SDL.h"
#include "Graphics.h"
#include "Position.h"
#include <Tuple>
#include <stdexcept>
#include <sstream>

GameObject::GameObject(Graphics* graphics, std::tuple<lua_State*, luabridge::LuaRef> luaRef)
{
	Initialise(graphics, std::get<0>(luaRef), std::get<1>(luaRef));
}


GameObject::~GameObject()
{
}

void GameObject::Draw(SDL_Surface * screen)
{
	SDL_BlitSurface(GetCurrentImage(), NULL, screen, new SDL_Rect(Location));
}

void GameObject::SetCollision(luabridge::LuaRef ref)
{
	Collision.clear();

	if (ref.isNil())
	{
		return;
	}
	if (!ref.isTable())
	{
		std::runtime_error("Invalid value for collision, expects table");
	}

	for (int i = 1; i <= ref.length(); i++)
	{
		SDL_Rect rect;
		auto crect = ref[i];
		if (!crect.isTable())
		{
			std::runtime_error("Invalid value for collision, expects table of lists");
		}
		else if (!crect.length() == 4)
		{
			std::runtime_error("Invalid value for collision, expects table of lists of length 4");
		}
		rect.x = GetInt(crect, 1, "collision");
		rect.y = GetInt(crect, 2, "collision");
		rect.w = GetInt(crect, 3, "collision");
		rect.h = GetInt(crect, 4, "collision");
		Collision.push_back(rect);
	}
}

std::tuple<lua_State*, luabridge::LuaRef> GameObject::SetupLua(std::string file, std::string type)
{
	lua_State* L = luaL_newstate();

	if (luaL_dofile(L, file.data()))
	{
		std::stringstream error;
		error << "luaL_dofile failed: " << lua_tostring(L, -1);
		throw std::runtime_error(error.str());
	}
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);

	luabridge::getGlobalNamespace(L)
		.beginClass<Position>("position")
		.addProperty("x", &Position::getX, &Position::setX)
		.addProperty("y", &Position::getY, &Position::setY)
		.addProperty("state", &Position::getState, &Position::setState);

	return std::make_tuple(L, luabridge::getGlobal(L, type.data()));
}

void GameObject::SetPosition(int x, int y)
{
	Location.x = x;
	Location.y = y;
}

bool GameObject::CheckCollision(GameObject * otherObject)
{
	std::vector<SDL_Rect> collision1 = this->Collision;
	std::vector<SDL_Rect> collision2 = otherObject->Collision;
	for (unsigned int i = 0; i < collision1.size(); i++)
	{
		int left1 = Location.x + collision1[i].x;
		int top1 = Location.y + collision1[i].y;
		int right1 = left1 + collision1[i].w;
		int bottom1 = top1 + collision1[i].h;

		for (unsigned int j = 0; j < collision2.size(); j++)
		{
			int left2 = otherObject->Location.x + collision2[j].x;
			int top2 = otherObject->Location.y + collision2[j].y;
			int right2 = left2 + collision2[j].w;
			int bottom2 = top2 + collision2[j].h;

			if (left1 < right2 && left2 < right1 && top1 < bottom2 && top2 < bottom1)
			{
				return true;
			}
		}
	}
	return false;
}

void GameObject::DoUpdate(GameState* state)
{
	// Override in derived class
}

bool GameObject::IsOutOfBounds(GameState* state)
{
	return Location.x < -Location.w 
		|| Location.x > state->ScreenWidth 
		|| Location.y < -Location.h 
		|| Location.y > state->ScreenHeight;
}

SDL_Surface * GameObject::GetCurrentImage()
{
	return Image;
}

void GameObject::Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref)
{
	SetCollision(ref["collision"]);

	Image = graphics->LoadImage(GetString(ref, "image", "none"));

	SDL_Rect rect = GetCurrentImage()->clip_rect;
	Location.w = rect.w;
	Location.h = rect.h;
}

int GameObject::GetInt(luabridge::LuaRef ref, std::string key, int defaultValue)
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

int GameObject::GetInt(luabridge::LuaRef ref, std::string key, int index, int defaultValue)
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

int GameObject::GetInt(luabridge::LuaRef ref, int index, std::string parent)
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

std::string GameObject::GetString(luabridge::LuaRef ref, std::string key, std::string defaultValue)
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

luabridge::LuaRef GameObject::GetFunction(luabridge::LuaRef ref, std::string key)
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

