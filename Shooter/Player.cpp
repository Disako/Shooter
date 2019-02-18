#include "Player.h"
#include "SDL.h"


Player::Player()
{
	Initialise();
}


Player::~Player()
{
	Initialise();
}

void Player::Dispose()
{
	SDL_FreeSurface(Image);
}

void Player::DoUpdate(Uint8 *keys, GameObject* gameObjects[], int gameObjectCount)
{
	if (keys[SDLK_UP])
	{
		Location.y--;
	}
	if (keys[SDLK_DOWN])
	{
		Location.y++;
	}
	if (keys[SDLK_LEFT])
	{
		Location.x--;
	}
	if (keys[SDLK_RIGHT])
	{
		Location.x++;
	}
}

void Player::Initialise()
{
	Image = SDL_DisplayFormat(SDL_LoadBMP("images\\Ship.bmp"));

	Uint32 colorkey = SDL_MapRGB(Image->format, 0, 0xFF, 0);

	SDL_SetColorKey(Image, SDL_SRCCOLORKEY, colorkey);
}

SDL_Surface* Player::GetCurrentImage()
{
	return Image;
}