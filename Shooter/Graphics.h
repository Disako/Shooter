#pragma once
#include "SDL.h"
#include <string>
#include <map>

class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Surface* LoadImage(std::string filename);

private:
	std::map<std::string, SDL_Surface*> AddedImages;
};

