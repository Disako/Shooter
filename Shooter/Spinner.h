#pragma once
#include "Enemy.h"
#include "Graphics.h"

class Spinner :
	public Enemy
{
public:
	Spinner(Graphics* graphics, bool goingRight);
	~Spinner() override;
	void DoUpdate(GameState* state) override;
	std::vector<SDL_Rect> GetCollison() override;
protected:
	SDL_Surface* GetCurrentImage() override;
	void Initialise(Graphics* graphics) override;
private:
	SDL_Surface* Image;
	bool GoingRight;
};

