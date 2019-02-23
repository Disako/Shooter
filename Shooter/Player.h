#pragma once
#include "GameObject.h"
#include <vector>
#include <string>

struct Weapon
{
	luabridge::LuaRef Ref = NULL;
	int Reload;
	std::string InitialState;
	int PositionX, PositionY;
	lua_State* L;
	int RemainingReload = 0;
	Resources* ResourcesStore;
	Mix_Chunk* FireSound;
	int FireVolume;
};

class Player :
	public GameObject
{
public:
	Player(Resources* resources, lua_State* L);
	~Player() override;
	void DoUpdate(GameState* state) override;
private:
	Player(Resources* resources, lua_State* L, luabridge::LuaRef ref);
	void Initialise(Resources* resources, lua_State* L, luabridge::LuaRef ref);
	SDL_Rect Speed;
	int Reload;
	std::vector<Weapon> Weapons;
};

