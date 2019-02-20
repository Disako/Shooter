#pragma once
#include "SDL.h"
#include <string>
#include <vector>

class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Surface* Player;
	SDL_Surface* Spinner;
	SDL_Surface* BasicBullet;

private:
	SDL_Surface* LoadImage(std::string filename);
	std::vector<SDL_Surface*> AddedImages;
};

