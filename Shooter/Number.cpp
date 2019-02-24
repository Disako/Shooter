#include "Number.h"
#include <stdexcept>



Number::Number(Resources* resources)
{
	Image = resources->LoadImage("Images\\Numbers.bmp");
	auto w = Image->clip_rect.w / 5;
	auto h = Image->clip_rect.h / 2;

	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 5; j++)
		{
			SDL_Rect rect;
			rect.x = j * w;
			rect.y = i * h;
			rect.w = w;
			rect.h = h;
			Frames[j + i * 5] = rect;
		}
	}
}


Number::~Number()
{
}

void Number::Draw(SDL_Surface * screen, unsigned int number, int x, int y, Alignment alignment)
{
	auto digits = number > 0 ? (int)log10((double)number) + 1 : 1;
	auto width = digits * Frames[0].w;
	switch (alignment)
	{
	case Left:
		break;
	case Right:
		x -= width;
		break;
	case Center:
		x -= width / 2;
		break;
	default:
		std::runtime_error("Invalid alignment");
	}
	for (unsigned int i = 0; i < digits; i++)
	{
		int multiplier = (int)pow(10, digits - 1 - i);
		auto digit = number / multiplier;

		SDL_Rect position;
		position.x = x;
		position.y = y;
		position.w = Frames[digit].w;
		position.h = Frames[digit].h;

		SDL_BlitSurface(Image, &SDL_Rect(Frames[digit]), screen, &position);

		number -= multiplier * digit;
		x += Frames[digit].w;
	}
}
