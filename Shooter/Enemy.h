#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "AutoMove.h"
#include <tuple>

struct Spawn
{
	luabridge::LuaRef Ref = NULL;
	int Reload;
	std::string InitialState;
	int PositionX, PositionY;
	lua_State* L;
	int RemainingReload = 0;
	Resources* ResourcesStore;
	Mix_Chunk* SpawnSound;
	int SpawnVolume;
};

class Enemy :
	public AutoMove
{
public:
	Enemy(Resources* resources, lua_State* L, std::string type, std::string initialState);
	~Enemy();
	void Damage(unsigned int damage);
	bool Immune;
	void DoUpdate(GameState* state) override;
	unsigned int Score;
private:
	int HP;
	Enemy(Resources* resources, lua_State* L, luabridge::LuaRef ref, std::string initialState);
	void Initialise(Resources* resources, lua_State* L, luabridge::LuaRef ref);
	std::vector<Spawn> Spawns;
};

