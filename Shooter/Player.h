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
	int RemainingReload = 0;
	Mix_Chunk* FireSound;
	int FireVolume;
	int SoundFrequency;
	int LastSound = 0;
	int MinLevel;
	int MaxLevel;
};

class Player :
	public GameObject
{
public:
	Player(Resources* resources, lua_State* L, std::string playerType);
	~Player() override;
	void DoUpdate(GameState* state) override;
	void SetLevel(int level, bool setFrame, GameState* state);
private:
	Player(Resources* resources, lua_State* L, luabridge::LuaRef ref);
	void Initialise(Resources* resources, lua_State* L, luabridge::LuaRef ref);
	SDL_Rect Speed;
	int Reload;
	std::vector<Weapon> Weapons;
	int Invincibility;
	Resources* ResourcesStore;
	int Level;
	int MaxLevel;
	luabridge::LuaRef CollisionRefs = nullptr;
	int LastChange;
};

