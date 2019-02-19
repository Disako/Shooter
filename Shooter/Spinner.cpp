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
		Destroy(state);
	}
}

void Spinner::Initialise(Graphics* graphics)
{
	Image = graphics->Spinner;

	GameObject::Initialise(graphics);
}

SDL_Surface * Spinner::GetCurrentImage()
{
	return Image;
}
