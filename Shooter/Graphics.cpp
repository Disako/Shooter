#include "Graphics.h"
#include <sstream>


Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	for (auto& x : AddedImages)
		SDL_FreeSurface(x.second);
}

SDL_Surface* Graphics::LoadImage(std::string filename)
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

	image = SDL_DisplayFormat(image);

	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0xFF, 0);

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);

	AddedImages[filename] = image;

	return image;
}
