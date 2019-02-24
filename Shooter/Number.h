#pragma once
#include "SDL.h"
#include "Resources.h"
#include <vector>

enum Alignment
{
	Left = 0,
	Right = 1,
	Center = 2
};

class Number
{
public:
	Number(Resources* resources);
	~Number();
	void Draw(SDL_Surface * screen, unsigned int number, int x, int y, Alignment alignment);
private:
	SDL_Surface* Image;
	SDL_Rect Frames[10];
};

