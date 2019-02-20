#include "GameObject.h"
#include "SDL.h"
#include "Graphics.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Draw(SDL_Surface * screen)
{
	SDL_BlitSurface(GetCurrentImage(), NULL, screen, new SDL_Rect(Location));
}

void GameObject::Destroy(GameState* state)
{
	state->GameObjects.erase(std::find(state->GameObjects.begin(), state->GameObjects.end(), this), state->GameObjects.end());
	delete this;
}

std::vector<SDL_Rect> GameObject::GetCollison()
{
	return std::vector<SDL_Rect>();
}

bool GameObject::CheckCollision(GameObject * otherObject)
{
	std::vector<SDL_Rect> collision1 = this->GetCollison();
	std::vector<SDL_Rect> collision2 = otherObject->GetCollison();
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
	return nullptr;
}

void GameObject::Initialise(Graphics* graphics)
{
	SDL_Rect rect = GetCurrentImage()->clip_rect;
	Location.w = rect.w;
	Location.h = rect.h;
}

