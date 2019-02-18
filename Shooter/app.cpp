#include "SDL.h"
#include "Player.h"
#include "SDL_timer.h"

void DoUpdate(Uint8 *keys, GameObject* gameObjects[], int objectCount);
void DrawScreen(SDL_Surface* screen, GameObject* gameObjects[], int objectCount);

int main(int argc, char* args[])
{
	SDL_Surface* screen = NULL;
	SDL_Event event;
	Uint8 *keystates;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

	Player* ship = new Player();
	
	ship->Location.x = 100;
	ship->Location.y = 100;

	GameObject* objects[1] = { ship };

	Uint32 lastRefreshTicks = SDL_GetTicks();

	do
	{
		SDL_PollEvent(&event);
		keystates = SDL_GetKeyState(NULL);
		DoUpdate(keystates, objects, 1);
		DrawScreen(screen, objects, 1);

		Uint32 currentTicks;

		do {
			currentTicks = SDL_GetTicks();
		} while (currentTicks < lastRefreshTicks + 17);

		SDL_Flip(screen);

		lastRefreshTicks = currentTicks;

	} while (!(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT));

	ship->Dispose();

	SDL_Quit();

	return 0;
}

void DoUpdate(Uint8 *keys, GameObject* gameObjects[], int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		gameObjects[i]->DoUpdate(keys, gameObjects, objectCount);
	}
}

void DrawScreen(SDL_Surface* screen, GameObject* gameObjects[], int objectCount)
{
	SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));

	for (int i = 0; i < objectCount; i++)
	{
		gameObjects[i]->Draw(screen);
	}
}