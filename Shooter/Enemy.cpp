#include "Enemy.h"
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "Position.h"

Enemy::Enemy(Resources* resources, lua_State* L, std::string type, std::string initialState) : Enemy(resources, L, LuaLoadedObject::GetRef(L, type), initialState)
{
}

Enemy::Enemy(Resources* resources, lua_State* L, luabridge::LuaRef ref, std::string initialState) : AutoMove(resources, L, ref, initialState)
{
	Initialise(resources, L, ref);
}

Enemy::~Enemy()
{
}

void Enemy::Initialise(Resources * resources, lua_State* L, luabridge::LuaRef ref)
{
	HP = GetInt(ref, "hp", 1);
}

void Enemy::Damage(unsigned int damage)
{
	HP -= damage;

	if (HP <= 0) Destroyed = true;
}
