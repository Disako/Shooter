#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();
	void Dispose();
	void DoUpdate(GameState* state) override;
protected:
	SDL_Surface* GetCurrentImage() override;
	void Initialise() override;
private:
	SDL_Surface* Image;
	SDL_Rect Speed;
};

