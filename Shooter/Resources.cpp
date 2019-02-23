#include "Resources.h"
#include <sstream>


Resources::Resources(SDL_Window* window)
{
	Window = window;
}


Resources::~Resources()
{
	for (auto& x : AddedImages)
		SDL_FreeSurface(x.second);
	for (auto& x : AddedSounds)
		Mix_FreeChunk(x.second);
	for (auto& x : AddedMusic)
		Mix_FreeMusic(x.second);
}

SDL_Surface* Resources::LoadImage(std::string filename)
{
	SDL_Surface* image = AddedImages[filename];

	if (image)
		return image;

	image = SDL_LoadBMP(filename.data());
	if (!image)
	{
		std::stringstream error;
		error << "Could not find image: " << filename;
		throw std::runtime_error(error.str());
	}

	image = SDL_ConvertSurfaceFormat(image, SDL_GetWindowPixelFormat(Window), 0);

	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0xFF, 0);

	SDL_SetColorKey(image, SDL_TRUE, colorkey);

	AddedImages[filename] = image;

	return image;
}

Mix_Chunk* Resources::LoadSound(std::string filename)
{
	Mix_Chunk* sound = AddedSounds[filename];

	if (sound)
		return sound;

	sound = Mix_LoadWAV(filename.data());

	if (!sound)
	{
		std::stringstream error;
		error << "Could not find sound: " << filename;
		throw std::runtime_error(error.str());
	}

	AddedSounds[filename] = sound;

	return sound;
}

Mix_Music * Resources::LoadMusic(std::string filename)
{
	Mix_Music* music = AddedMusic[filename];

	if (music)
		return music;

	music = Mix_LoadMUS(filename.data());

	if (!music)
	{
		std::stringstream error;
		error << "Could not find music: " << filename;
		throw std::runtime_error(error.str());
	}

	AddedMusic[filename] = music;

	return music;
}
