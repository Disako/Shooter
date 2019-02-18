#include "SDL.h"
#include "GameState.h"

#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	SDL_Rect Location;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);

protected:
	virtual SDL_Surface* GetCurrentImage();
	virtual void Initialise();

};

