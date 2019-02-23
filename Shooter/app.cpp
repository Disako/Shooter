#include "SDL.h"
#include "Player.h"
#include "SDL_timer.h"
#include "Resources.h"
#include "Enemy.h"
#include <vector>
#include <sstream>
#include <string>
#include "Position.h"
#include "Level.h"

void CreateShip(GameState* state, Resources* resources, lua_State* L);
Level* DoUpdate(GameState* state, Resources* resources, Level* level);
void DrawScreen(SDL_Surface* screen, GameState* state);
lua_State* SetupLua();

int main(int argc, char* args[])
{
	SDL_Event event;

	GameState* state = new GameState();

	state->ScreenWidth = 640;
	state->ScreenHeight = 480;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	auto window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, state->ScreenWidth, state->ScreenHeight, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(window);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	Resources* resources = new Resources(window);

	lua_State* L = SetupLua();
	
	CreateShip(state, resources, L);

	Uint32 lastRefreshTicks = SDL_GetTicks();

	auto level = new Level(L, "level1");

	do
	{
		SDL_PollEvent(&event);
		state->Keys = SDL_GetKeyboardState(NULL);
		level = DoUpdate(state, resources, level);
		DrawScreen(screen, state);

		Uint32 currentTicks;

		currentTicks = SDL_GetTicks();
		if(lastRefreshTicks + 17 > currentTicks)
			SDL_Delay(lastRefreshTicks + 17 - currentTicks);

		SDL_UpdateWindowSurface(window);

		lastRefreshTicks = SDL_GetTicks();

	} while (!(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT));

	delete state;
	delete resources;

	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

lua_State* SetupLua()
{
	lua_State* L = luaL_newstate();

	const int fileCount = 3;
	std::string files[fileCount] = { "Definitions\\Enemies.lua", "Definitions\\Player.lua", "Definitions\\Levels.lua" };

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
		.addProperty("frame", &Position::getFrame, &Position::setFrame)
		.addProperty("count", &Position::getCount, &Position::setCount)
		.addProperty("state", &Position::getState, &Position::setState);

	return L;
}

void CreateShip(GameState* state, Resources* resources, lua_State* L)
{
	Player* ship = new Player(resources, L);

	ship->Location.x = 100;
	ship->Location.y = 100;

	state->GameObjects.push_back(ship);
}

Level* DoUpdate(GameState* state, Resources* resources, Level* level)
{
	level = level->DoUpdate(state, resources);

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

	return level;
}

void DrawScreen(SDL_Surface* screen, GameState* state)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		state->GameObjects[i]->Draw(screen);
	}
}