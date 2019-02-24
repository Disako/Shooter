#include "Level.h"
#include <sstream>
#include "Enemy.h"
#include "Player.h"
#include "BackgroundObject.h"

Level::Level(lua_State* L, std::string levelName)
{

	this->L = L;
	auto ref = LuaLoadedObject::GetRef(L, levelName);

	if (ref.length() == 0)
	{
		std::stringstream error;
		error << levelName << "Must have at least 1 action";
		throw std::runtime_error(error.str());
	}

	for (int i = 1; i <= ref.length(); i++)
	{
		Events.push_back(ref[i]);
	}
}


Level::~Level()
{
}

Level* Level::DoUpdate(GameState* state, Resources* resources) 
{
	while (Wait == 0)
	{
		if (Index >= Events.size()) Index = 0;

		auto action = GetString(Events[Index], "action", "none");

		if (action == "player")
		{
			auto player = new Player(resources, L, GetString(Events[Index], "player", "None"));
			player->Location.x = GetInt(Events[Index], "location", 1, 0);
			player->Location.y = GetInt(Events[Index], "location", 2, 0);
			player->SetLevel(GetInt(Events[Index], "level", 1), true);

			state->GameObjects.push_back(player);
		}
		else if (action == "spawn")
		{
			auto enemy = new Enemy(resources, L, GetString(Events[Index], "enemy", "blank"), GetString(Events[Index], "state", "None"));
			enemy->Location.x = GetInt(Events[Index], "location", 1, 0);
			enemy->Location.y = GetInt(Events[Index], "location", 2, 0);

			state->GameObjects.push_back(enemy);
		}
		else if (action == "wait")
		{
			Wait = GetInt(Events[Index], "frames", 1);
		}
		else if (action == "level")
		{
			auto nextLevel = new Level(L, GetString(Events[Index], "level", "blank"));
			return nextLevel->DoUpdate(state, resources);
		}
		else if (action == "music")
		{
			auto musicName = GetString(Events[Index], "file", "none");
			if (musicName != resources->CurrentMusic)
			{
				if (Mix_PlayingMusic())
				{
					Mix_FadeOutMusic(GetInt(Events[Index], "fade", 1));
				}
				auto music = resources->LoadMusic(musicName);
				Mix_VolumeMusic(GetInt(Events[Index], "volume", 100));
				Mix_FadeInMusic(music, -1, GetInt(Events[Index], "fade", 1));
				resources->CurrentMusic = musicName;
			}
		}
		else if (action == "stopmusic")
		{
			if (Mix_PlayingMusic())
			{
				Mix_FadeOutMusic(GetInt(Events[Index], "fade", 1));
				resources->CurrentMusic = "";
			}
		}
		else if (action == "backgroundObj")
		{
			BackgroundSpawn spawn;
			auto type = GetString(Events[Index], "type", "none");
			spawn.probability = GetInt(Events[Index], "probability", 0);
			spawn.initialState = GetString(Events[Index], "state", "none");
			state->BackgroundSpawns[type] = spawn;

			if (spawn.probability > 0 && GetBool(Events[Index], "fill", false))
			{
				auto prob = spawn.probability * GetInt(GetRef(L, type), "fillMultiplier", 1);
				while (prob >= 100)
				{
					auto obj = new BackgroundObject(resources, L, type, spawn.initialState, true);
					state->BackgroundObjects.push_back(obj);
					prob -= 100;
				}
				if (rand() % 100 < prob)
				{
					auto obj = new BackgroundObject(resources, L, type, spawn.initialState, true);
					state->BackgroundObjects.push_back(obj);
				}
			}
		}
		else
		{
			std::stringstream error;
			error << "Unknown level action: " << action;
			throw std::runtime_error(error.str());
		}

		Index++;
	}

	Wait--;

	return this;
}