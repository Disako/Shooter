#include "SDL.h"
#include "GameState.h"
#include "Graphics.h"

#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	SDL_Rect Location;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);
	bool IsOutOfBounds(GameState* state);
	void Destroy(GameState* state);
protected:
	virtual SDL_Surface* GetCurrentImage();
	virtual void Initialise(Graphics* graphics);

};

