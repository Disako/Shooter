#include "Enemy.h"
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "Position.h"

Enemy::Enemy(Graphics* graphics, lua_State* L, std::string type, std::string initialState) : Enemy(graphics, L, GameObject::GetRef(L, type), initialState)
{
}

Enemy::Enemy(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState) : AutoMove(graphics, L, ref, initialState)
{
	Initialise(graphics, L, ref);
}

Enemy::~Enemy()
{
}

void Enemy::Initialise(Graphics * graphics, lua_State* L, luabridge::LuaRef ref)
{
	HP = GetInt(ref, "hp", 1);
}

void Enemy::Damage(unsigned int damage)
{
	HP -= damage;

	if (HP <= 0) Destroyed = true;
}
