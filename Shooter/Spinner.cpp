#include "Spinner.h"
#include <vector>


Spinner::Spinner(Graphics* graphics, bool goingRight)
{
	GoingRight = goingRight;
	Initialise(graphics);
}


Spinner::~Spinner()
{
}

void Spinner::DoUpdate(GameState * state)
{
	if (GoingRight)
	{
		Location.x++;
	}
	else
	{
		Location.x--;
	}
	Location.y++;

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

std::vector<SDL_Rect> Spinner::GetCollison()
{
	SDL_Rect r1, r2, r3;
	r1.x = 29;
	r1.y = 23;
	r1.w = 22;
	r1.h = 37;

	r2.x = 14;
	r2.y = 14;
	r2.w = 15;
	r2.h = 22;

	r3.x = 51;
	r3.y = 14;
	r3.w = 15;
	r3.h = 22;

	return { r1, r2, r3 };
}

void Spinner::Initialise(Graphics* graphics)
{
	Image = graphics->Spinner;
	HP = 1;

	GameObject::Initialise(graphics);
}

SDL_Surface * Spinner::GetCurrentImage()
{
	return Image;
}
