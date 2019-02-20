#include "Graphics.h"



Graphics::Graphics()
{
	Player = LoadImage("images\\Ship.bmp");
	Spinner = LoadImage("images\\Spinner.bmp");
	BasicBullet = LoadImage("images\\BasicBullet.bmp");
}


Graphics::~Graphics()
{
	for (unsigned int i = 0; i < AddedImages.size(); i++)
		SDL_FreeSurface(AddedImages[i]);
}

SDL_Surface* Graphics::LoadImage(std::string filename)
{
	SDL_Surface* image = SDL_DisplayFormat(SDL_LoadBMP(filename.data()));

	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0xFF, 0);

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);

	AddedImages.push_back(image);

	return image;
}
