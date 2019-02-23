#include "SDL.h"
#include "Player.h"
#include "SDL_timer.h"
#include "Graphics.h"
#include "Enemy.h"
#include <vector>
#include <sstream>
#include <string>
#include "Position.h"

void CreateShip(GameState* state, Graphics* graphics, lua_State* L);
void DoUpdate(GameState* state);
void DrawScreen(SDL_Surface* screen, GameState* state);
void AddEnemy(GameState* state, Graphics* graphics, lua_State* L);
lua_State* SetupLua();

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

	lua_State* L = SetupLua();
	
	CreateShip(state, graphics, L);

	Uint32 lastRefreshTicks = SDL_GetTicks();

	AddEnemy(state, graphics, L);

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

lua_State* SetupLua()
{
	lua_State* L = luaL_newstate();

	const int fileCount = 2;
	std::string files[fileCount] = { "Definitions\\Enemies.lua", "Definitions\\Player.lua" };

	for (unsigned int i = 0; i < fileCount; i++)
	{
		if (luaL_dofile(L, files[i].data()))
		{
			std::stringstream error;
			error << "luaL_dofile failed: " << lua_tostring(L, -1);
			throw std::runtime_error(error.str());
		}
	}
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);

	luabridge::getGlobalNamespace(L)
		.beginClass<Position>("position")
		.addProperty("x", &Position::getX, &Position::setX)
		.addProperty("y", &Position::getY, &Position::setY)
		.addProperty("state", &Position::getState, &Position::setState);

	return L;
}

void AddEnemy(GameState* state, Graphics* graphics, lua_State* L)
{
	Enemy* enemy = new Enemy(graphics, L, "spinner", "right");

	enemy->Location.x = state->ScreenWidth / 2;
	enemy->Location.y = -enemy->Location.h;

	state->GameObjects.push_back(enemy);
}

void CreateShip(GameState* state, Graphics* graphics, lua_State* L)
{
	Player* ship = new Player(graphics, L);

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

	std::vector<int> indexesToDelete = std::vector<int>();

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		if (state->GameObjects[i]->Destroyed)
		{
			indexesToDelete.push_back(i);
		}
	}

	for (int i = indexesToDelete.size() - 1; i >= 0; i--)
	{
		delete state->GameObjects[indexesToDelete[i]];
		state->GameObjects.erase(state->GameObjects.begin() + indexesToDelete[i]);
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