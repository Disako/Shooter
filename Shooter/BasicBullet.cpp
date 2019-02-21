#include "BasicBullet.h"



BasicBullet::BasicBullet(Graphics* graphics)
{
	Initialise(graphics);
}


BasicBullet::~BasicBullet()
{
}

void BasicBullet::Initialise(Graphics* graphics)
{
	Image = graphics->LoadImage("images\\BasicBullet.bmp");

	Collision = GetCollison();

	GameObject::Initialise(graphics);
}

unsigned int BasicBullet::GetDamage()
{
	return 1;
}

SDL_Surface * BasicBullet::GetCurrentImage()
{
	return Image;
}

void BasicBullet::DoUpdate(GameState * state)
{
	Location.y -= 10;

	PlayerShot::DoUpdate(state);
}

std::vector<SDL_Rect> BasicBullet::GetCollison()
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 6;
	rect.h = 6;

	return { rect };
}
