#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();
	void Dispose();
	void DoUpdate(Uint8 *keys, GameObject* gameObjects[], int gameObjectCount, int screenWidth, int screenHeight) override;
protected:
	SDL_Surface* GetCurrentImage() override;
	void Initialise() override;
private:
	SDL_Surface* Image;
	SDL_Rect Speed;
};

