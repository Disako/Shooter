extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "GameObject.h"
#include "SDL.h"
#include "Resources.h"
#include "Position.h"
#include <Tuple>
#include <stdexcept>
#include <sstream>

GameObject::GameObject(Resources* resources, lua_State* L, luabridge::LuaRef ref)
{
	Initialise(resources, L, ref);
}


GameObject::~GameObject()
{
}

void GameObject::Draw(SDL_Surface * screen)
{
	SDL_BlitSurface(GetCurrentImage(), new SDL_Rect(Frames[Frame]), screen, new SDL_Rect(Location));
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
		else if (crect.length() != 4)
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

void GameObject::Initialise(Resources* resources, lua_State* L, luabridge::LuaRef ref)
{
	SetCollision(ref["collision"]);

	Image = resources->LoadImage(GetString(ref, "image", "none"));

	Frame = GetInt(ref, "initialFrame", 0);

	auto frameWidth = GetInt(ref, "frameSize", 1, 0);
	auto frameHeight = GetInt(ref, "frameSize", 2, 0);

	Frames.clear();

	if (frameWidth == 0 || frameHeight == 0)
	{
		SDL_Rect rect = GetCurrentImage()->clip_rect;
		Location.w = rect.w;
		Location.h = rect.h;

		SDL_Rect frame;
		frame.x = 0;
		frame.y = 0;
		frame.w = rect.w;
		frame.h = rect.h;
		Frames.push_back(frame);
	}
	else
	{
		Location.w = frameWidth;
		Location.h = frameHeight;

		SDL_Rect rect = GetCurrentImage()->clip_rect;

		int x = 0;
		int y = 0;

		while (y + frameHeight <= rect.h)
		{
			while (x + frameWidth <= rect.w)
			{
				SDL_Rect frame;
				frame.x = x;
				frame.y = y;
				frame.w = frameWidth;
				frame.h = frameHeight;
				Frames.push_back(frame);

				x+= frameWidth;
			}
			x = 0;
			y += frameHeight;
		}
	}
}

