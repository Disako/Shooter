#include "SDL.h"
#include "Player.h"
#include "SDL_timer.h"

void CreateShip(GameState* state);
void DoUpdate(GameState* state);
void DrawScreen(SDL_Surface* screen, GameState* state);

int main(int argc, char* args[])
{
	SDL_Surface* screen = NULL;
	SDL_Event event;

	GameState* state = new GameState();

	state->ScreenWidth = 640;
	state->ScreenHeight = 480;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(state->ScreenWidth, state->ScreenHeight, 32, SDL_SWSURFACE);
	
	CreateShip(state);

	Uint32 lastRefreshTicks = SDL_GetTicks();

	do
	{
		SDL_PollEvent(&event);
		state->Keys = SDL_GetKeyState(NULL);
		DoUpdate(state);
		DrawScreen(screen, state);

		Uint32 currentTicks;

		do {
			currentTicks = SDL_GetTicks();
		} while (currentTicks < lastRefreshTicks + 17);

		SDL_Flip(screen);

		lastRefreshTicks = currentTicks;

	} while (!(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT));

	delete state;

	SDL_Quit();

	return 0;
}

void CreateShip(GameState* state)
{
	Player* ship = new Player();

	ship->Location.x = 100;
	ship->Location.y = 100;

	state->GameObjects.push_back(ship);
}

void DoUpdate(GameState* state)
{
	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		state->GameObjects[i]->DoUpdate(state);
	}
}

void DrawScreen(SDL_Surface* screen, GameState* state)
{
	SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		state->GameObjects[i]->Draw(screen);
	}
}