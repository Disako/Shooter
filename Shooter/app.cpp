#include "SDL.h"
#include "Player.h"
#include "SDL_timer.h"
#include "Graphics.h"
#include "Spinner.h"

void CreateShip(GameState* state, Graphics* graphics);
void DoUpdate(GameState* state);
void DrawScreen(SDL_Surface* screen, GameState* state);
void AddEnemy(GameState* state, Graphics* graphics);

int main(int argc, char* args[])
{
	SDL_Surface* screen = NULL;
	SDL_Event event;

	GameState* state = new GameState();

	state->ScreenWidth = 640;
	state->ScreenHeight = 480;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(state->ScreenWidth, state->ScreenHeight, 32, SDL_SWSURFACE);

	Graphics* graphics = new Graphics();
	
	CreateShip(state, graphics);

	Uint32 lastRefreshTicks = SDL_GetTicks();

	AddEnemy(state, graphics);

	do
	{

		SDL_PollEvent(&event);
		state->Keys = SDL_GetKeyState(NULL);
		DoUpdate(state);
		DrawScreen(screen, state);

		Uint32 currentTicks;

		currentTicks = SDL_GetTicks();
		if(lastRefreshTicks + 17 > currentTicks)
			SDL_Delay(lastRefreshTicks + 17 - currentTicks);

		SDL_Flip(screen);

		lastRefreshTicks = SDL_GetTicks();

	} while (!(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT));

	delete state;
	delete graphics;

	SDL_Quit();

	return 0;
}

void AddEnemy(GameState* state, Graphics* graphics)
{
	Spinner* enemy = new Spinner(graphics, true);

	enemy->Location.x = state->ScreenWidth / 2;
	enemy->Location.y = -enemy->Location.h;

	state->GameObjects.push_back(enemy);
}

void CreateShip(GameState* state, Graphics* graphics)
{
	Player* ship = new Player(graphics);

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