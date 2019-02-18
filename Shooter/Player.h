#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();
	void Dispose();
	void DoUpdate(Uint8 *keys, GameObject* gameObjects[], int gameObjectCount) override;
protected:
	SDL_Surface* GetCurrentImage() override;
private:
	void Initialise();
	SDL_Surface* Image;
};

