#include "SDL.h"

#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	SDL_Rect Location;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(Uint8 *keys, GameObject* gameObjects[], int gameObjectCount);

protected:
	virtual SDL_Surface* GetCurrentImage();

};

