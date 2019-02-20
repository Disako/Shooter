#pragma once
#include "PlayerShot.h"
class BasicBullet :
	public PlayerShot
{
public:
	BasicBullet(Graphics* graphics);
	~BasicBullet();
	void Initialise(Graphics* graphics) override;

	unsigned int GetDamage() override;
	SDL_Surface* GetCurrentImage() override;
	void DoUpdate(GameState* state) override;
	std::vector<SDL_Rect> GetCollison() override;
private:
	SDL_Surface* Image;
};

