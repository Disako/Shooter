#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player(Graphics* graphics);
	~Player() override;
	void DoUpdate(GameState* state) override;
	std::vector<SDL_Rect> GetCollison() override;
protected:
	SDL_Surface* GetCurrentImage() override;
	void Initialise(Graphics* graphics) override;
private:
	SDL_Surface* Image;
	SDL_Rect Speed;
};

