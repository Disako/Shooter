#include "Graphics.h"



Graphics::Graphics()
{
	Player = LoadImage("images\\Ship.bmp");
	Spinner = LoadImage("images\\Spinner.bmp");
}


Graphics::~Graphics()
{
	SDL_FreeSurface(Player);
	SDL_FreeSurface(Spinner);
}

SDL_Surface* Graphics::LoadImage(std::string filename)
{
	SDL_Surface* image = SDL_DisplayFormat(SDL_LoadBMP(filename.data()));

	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0xFF, 0);

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);

	return image;
}
