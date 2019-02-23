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
	Mix_Music* LoadMusic(std::string filename);
	std::string CurrentMusic;

private:
	std::map<std::string, SDL_Surface*> AddedImages;
	std::map<std::string, Mix_Chunk*> AddedSounds;
	std::map<std::string, Mix_Music*> AddedMusic;
	SDL_Window* Window;
};

