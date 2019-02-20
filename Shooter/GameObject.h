#include "SDL.h"
#include "GameState.h"
#include "Graphics.h"
#include <vector>

#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	SDL_Rect Location;
	bool Destroyed;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);
	bool IsOutOfBounds(GameState* state);
	void Destroy(GameState* state);
	virtual std::vector<SDL_Rect> GetCollison();
	bool CheckCollision(GameObject* otherObject);

protected:
	virtual SDL_Surface* GetCurrentImage();
	virtual void Initialise(Graphics* graphics);

};

