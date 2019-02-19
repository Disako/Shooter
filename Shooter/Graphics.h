#pragma once
#include "SDL.h"
#include <string>
class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Surface* Player;
	SDL_Surface* Spinner;

private:
	SDL_Surface* LoadImage(std::string filename);
};

