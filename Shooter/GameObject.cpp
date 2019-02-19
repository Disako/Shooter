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
	SDL_BlitSurface(GetCurrentImage(), NULL, screen, &Location);
}

void GameObject::Destroy(GameState* state)
{
	state->GameObjects.erase(std::find(state->GameObjects.begin(), state->GameObjects.end(), this), state->GameObjects.end());
	delete this;
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

