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
	Graphics* GraphicsStore;
};

class Player :
	public GameObject
{
public:
	Player(Graphics* graphics, lua_State* L);
	~Player() override;
	void DoUpdate(GameState* state) override;
private:
	Player(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	void Initialise(Graphics* graphics, lua_State* L, luabridge::LuaRef ref);
	SDL_Rect Speed;
	int Reload;
	std::vector<Weapon> Weapons;
};

