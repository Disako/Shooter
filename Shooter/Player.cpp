#include "Player.h"
#include "SDL.h"
#include "Graphics.h"


Player::Player(Graphics* graphics)
{
	Initialise(graphics);
}


Player::~Player()
{
}

void Player::DoUpdate(GameState* state)
{
	const int maxSpeed = 5;

	int up = 0, left = 0;

	if (state->Keys[SDLK_UP] || state->Keys[SDLK_w]) up++;
	if (Location.y > state->ScreenHeight - Location.h * 9 / 8) up++;
	if (state->Keys[SDLK_DOWN] || state->Keys[SDLK_s]) up--;
	if (Location.y < Location.h / 8) up--;

	if (state->Keys[SDLK_LEFT] || state->Keys[SDLK_a]) left++;
	if (Location.x > state->ScreenWidth - Location.w * 9 / 8) left++;
	if (state->Keys[SDLK_RIGHT] || state->Keys[SDLK_d]) left--;
	if (Location.x < Location.w / 8) left--;

	if (up > 0)
	{
		Speed.y--;
	}
	else if (up < 0)
	{
		Speed.y++;
	}
	else if (Speed.y < 0)
	{
		Speed.y++;
	}
	else if (Speed.y > 0)
	{
		Speed.y--;
	}

	if (left > 0)
	{
		Speed.x--;
	}
	else if (left < 0)
	{
		Speed.x++;
	}
	else if (Speed.x < 0)
	{
		Speed.x++;
	}
	else if (Speed.x > 0)
	{
		Speed.x--;
	}

	if (Speed.x > maxSpeed) Speed.x = maxSpeed;
	else if (Speed.x < -maxSpeed) Speed.x = -maxSpeed;
	if (Speed.y > maxSpeed) Speed.y = maxSpeed;
	else if (Speed.y < -maxSpeed) Speed.y = -maxSpeed;

	Location.x += Speed.x;
	Location.y += Speed.y;
}

void Player::Initialise(Graphics* graphics)
{
	Image = graphics->Player;

	GameObject::Initialise(graphics);
}

SDL_Surface* Player::GetCurrentImage()
{
	return Image;
}