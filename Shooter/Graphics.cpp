#include "Graphics.h"



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

	image = SDL_DisplayFormat(SDL_LoadBMP(filename.data()));

	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0xFF, 0);

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);

	AddedImages[filename] = image;

	return image;
}
