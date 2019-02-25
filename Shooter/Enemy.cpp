#include "Enemy.h"
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

Enemy::Enemy(Resources* resources, lua_State* L, std::string type, std::string initialState) : Enemy(resources, L, LuaLoadedObject::GetRef(L, type), initialState)
{
}

Enemy::Enemy(Resources* resources, lua_State* L, luabridge::LuaRef ref, std::string initialState) : AutoMove(resources, ref, initialState)
{
	Initialise(resources, L, ref);
}

Enemy::~Enemy()
{
}

void Enemy::Initialise(Resources * resources, lua_State* L, luabridge::LuaRef ref)
{
	HP = GetInt(ref, "hp", 1);
	Immune = GetBool(ref, "immune", false);
	Score = GetInt(ref, "score", 0);

	auto spawns = ref["spawns"];
	Spawns.clear();

	if (spawns.isNil()) return;
	if (!spawns.isTable())
	{
		throw std::runtime_error("Invalid value for spawns, expects list");
	}
	for (int i = 1; i <= spawns.length(); i++)
	{
		auto spawnRef = spawns[i];
		if (!spawnRef.isTable())
		{
			throw std::runtime_error("Invalid value for spawn, expects table");
		}
		Spawn spawn;
		std::string spawnTypeString = GetString(spawnRef, "identifier", "blank");
		spawn.Ref = GetRef(L, spawnTypeString.data());
		spawn.Reload = GetInt(spawnRef, "reload", 1);
		spawn.InitialState = GetString(spawnRef, "initialState", "none");
		spawn.PositionX = GetInt(spawnRef, "position", 1, 0);
		spawn.PositionY = GetInt(spawnRef, "position", 2, 0);
		spawn.L = L;
		spawn.RemainingReload = spawn.Reload;
		spawn.ResourcesStore = resources;
		auto spawnSound = GetString(spawnRef, "spawnSound", "");
		if (spawnSound != "")
		{
			spawn.SpawnSound = resources->LoadSound(spawnSound);
		}
		else
		{
			spawn.SpawnSound = nullptr;
		}
		spawn.SpawnVolume = GetInt(spawnRef, "spawnVolume", 100);

		Spawns.push_back(spawn);
	}
}

void Enemy::Damage(unsigned int damage)
{
	HP -= damage;

	if (HP <= 0) Destroyed = true;
}

void Enemy::DoUpdate(GameState * state)
{
	AutoMove::DoUpdate(state);

	for (unsigned int i = 0; i < Spawns.size(); i++)
	{
		if (Spawns[i].RemainingReload == 0)
		{
			auto spawn = new Enemy(Spawns[i].ResourcesStore, Spawns[i].L, Spawns[i].Ref, Spawns[i].InitialState);

			spawn->Location.x = Location.x + Spawns[i].PositionX;
			spawn->Location.y = Location.y + Spawns[i].PositionY;

			state->GameObjects.push_back(spawn);

			Spawns[i].RemainingReload = Spawns[i].Reload;

			if (Spawns[i].SpawnSound != nullptr)
			{
				Mix_VolumeChunk(Spawns[i].SpawnSound, (MIX_MAX_VOLUME * Spawns[i].SpawnVolume) / 100);
				Mix_PlayChannel(-1, Spawns[i].SpawnSound, 0);
			}
		}
		else if (Spawns[i].RemainingReload > 0)
		{
			Spawns[i].RemainingReload--;
		}
	}
}
