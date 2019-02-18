#include "GameObject.h"
#include "SDL.h"

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

void GameObject::DoUpdate(GameState* state)
{
	// Override in derived class
}

SDL_Surface * GameObject::GetCurrentImage()
{
	return nullptr;
}

void GameObject::Initialise()
{
	SDL_Rect rect = GetCurrentImage()->clip_rect;
	Location.w = rect.w;
	Location.h = rect.h;
}

