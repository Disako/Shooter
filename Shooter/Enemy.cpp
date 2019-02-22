#include "Enemy.h"
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "Position.h"

Enemy::Enemy(Graphics* graphics, std::string type, std::string initialState) : Enemy(graphics, GameObject::SetupLua("Definitions\\Enemies.lua", type), initialState)
{
}

Enemy::Enemy(Graphics* graphics, std::tuple<lua_State*, luabridge::LuaRef> luaRef, std::string initialState) : AutoMove(graphics, luaRef, initialState)
{
	Initialise(graphics, std::get<0>(luaRef), std::get<1>(luaRef));
}

Enemy::~Enemy()
{
}

SDL_Surface * Enemy::GetCurrentImage()
{
	return Image;
}

void Enemy::Initialise(Graphics * graphics, lua_State* L, luabridge::LuaRef ref)
{
	HP = ref["hp"];
}

void Enemy::Damage(unsigned int damage)
{
	HP -= damage;

	if (HP <= 0) Destroyed = true;
}
