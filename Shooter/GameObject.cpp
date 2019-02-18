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

void GameObject::DoUpdate(Uint8 *keys, GameObject* gameObjects[], int gameObjectCount)
{
	// Override in derived class
}

SDL_Surface * GameObject::GetCurrentImage()
{
	return nullptr;
}

