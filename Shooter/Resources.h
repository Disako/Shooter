#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include <string>
#include <map>

class Resources
{
public:
	Resources(SDL_Window* window);
	~Resources();

	SDL_Surface* LoadImage(std::string filename);
	Mix_Chunk* LoadSound(std::string filename);

private:
	std::map<std::string, SDL_Surface*> AddedImages;
	std::map<std::string, Mix_Chunk*> AddedSounds;
	SDL_Window* Window;
};

