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
#include "Number.h"
#include "BackgroundObject.h"

Level* DoUpdate(GameState* state, Resources* resources, Level* level, lua_State* L);
void DrawScreen(SDL_Surface* screen, GameState* state, Number* number, Resources* resources);
lua_State* SetupLua();

int main(int argc, char* args[])
{
	SDL_Event event;

	

	SDL_Init(SDL_INIT_EVERYTHING);
	
	const int screenWidth = 640;
	const int screenHeight = 480;

	auto window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(window);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	Resources* resources = new Resources(window);

	auto number = new Number(resources);

	lua_State* L = SetupLua();

	Uint32 lastRefreshTicks = SDL_GetTicks();

	bool quit = false;

	do
	{
		GameState* state = new GameState();

		state->ScreenWidth = screenWidth;
		state->ScreenHeight = screenHeight;
		auto level = new Level(L, "startUp");
		bool restart = false;

		do
		{
			SDL_PollEvent(&event);
			state->Keys = SDL_GetKeyboardState(NULL);
			level = DoUpdate(state, resources, level, L);
			DrawScreen(screen, state, number, resources);

			Uint32 currentTicks;

			currentTicks = SDL_GetTicks();
			if (lastRefreshTicks + 17 > currentTicks)
				SDL_Delay(lastRefreshTicks + 17 - currentTicks);

			SDL_UpdateWindowSurface(window);

			lastRefreshTicks = SDL_GetTicks();

			quit = event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT;
			restart = event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r;

		} while (!(quit || restart));

		delete state;

	} while (!quit);

	delete resources;

	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

lua_State* SetupLua()
{
	lua_State* L = luaL_newstate();

	const int fileCount = 4;
	std::string files[fileCount] = { 
		"Definitions\\Enemies.lua", 
		"Definitions\\Player.lua", 
		"Definitions\\Levels.lua",
		"Definitions\\Background.lua"
	};

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
		.addData("x", &Position::X, true)
		.addData("y", &Position::Y, true)
		.addData("frame", &Position::Frame, true)
		.addData("count", &Position::Count, true)
		.addData("state", &Position::State, true);

	return L;
}

void UpdateObjectList(std::vector<GameObject*>* objects, GameState* state, Resources* resources)
{
	for (unsigned int i = 0; i < objects->size(); i++)
	{
		objects->at(i)->DoUpdate(state);
	}

	std::vector<int> indexesToDelete = std::vector<int>();

	for (unsigned int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->Destroyed)
		{
			indexesToDelete.push_back(i);
		}
	}

	for (int i = indexesToDelete.size() - 1; i >= 0; i--)
	{
		objects->at(indexesToDelete[i])->Destroy(state, resources);
		delete objects->at(indexesToDelete[i]);
		objects->erase(objects->begin() + indexesToDelete[i]);
	}
}

Level* DoUpdate(GameState* state, Resources* resources, Level* level, lua_State* L)
{
	level = level->DoUpdate(state, resources);

	for (auto& spawn : state->BackgroundSpawns)
	{
		auto prob = spawn.second.probability;
		while (prob >= 100)
		{
			state->BackgroundObjects.push_back(new BackgroundObject(resources, L, spawn.first, spawn.second.initialState, false));
			prob -= 100;
		}
		if (rand() % 100 < prob)
		{
			state->BackgroundObjects.push_back(new BackgroundObject(resources, L, spawn.first, spawn.second.initialState, false));
		}
	}

	UpdateObjectList(&state->BackgroundObjects, state, resources);
	UpdateObjectList(&state->GameObjects, state, resources);

	return level;
}

void DrawScreen(SDL_Surface* screen, GameState* state, Number* number, Resources* resources)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	for (unsigned int i = 0; i < state->BackgroundObjects.size(); i++)
	{
		state->BackgroundObjects[i]->Draw(screen);
	}

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		state->GameObjects[i]->Draw(screen);
	}

	if (state->GameOver)
	{
		auto gameOver = resources->LoadImage("Images\\Gameover.bmp");
		auto location = SDL_Rect(gameOver->clip_rect);
		location.x = state->ScreenWidth / 2 - location.w / 2;
		location.y = state->ScreenHeight / 2 - location.h / 2;

		SDL_BlitSurface(gameOver, NULL, screen, &location);
		number->Draw(screen, state->Score, state->ScreenWidth / 2, location.y + location.h + 5, Alignment::Center);
	}
	else
	{
		number->Draw(screen, state->Score, state->ScreenWidth - 2, 2, Alignment::Right);
		if (state->ScoreMultiplier > 1)
		{
			auto x = resources->LoadImage("Images\\x.bmp");
			number->Draw(screen, state->ScoreMultiplier, state->ScreenWidth - 12, 22, Alignment::Right);
			SDL_Rect location;
			location.x = state->ScreenWidth - 12;
			location.y = 22;
			SDL_BlitSurface(x, NULL, screen, &location);
		}
	}
}