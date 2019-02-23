#include "PlayerShot.h"
#include "Enemy.h"
#include <tuple>

PlayerShot::PlayerShot(Graphics* graphics, lua_State* L, luabridge::LuaRef ref, std::string initialState) : AutoMove(graphics, L, ref, initialState)
{
	Initialise(graphics, L, ref);
}


PlayerShot::~PlayerShot()
{
}

void PlayerShot::DoUpdate(GameState * state)
{
	AutoMove::DoUpdate(state);

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(state->GameObjects[i]);
		if (enemy)
		{
			if (CheckCollision(enemy))
			{
				enemy->Damage(Damage);
				Destroyed = true;
			}
		}
	}
}

void PlayerShot::Initialise(Graphics * graphics, lua_State* L, luabridge::LuaRef ref)
{
	Damage = GetInt(ref, "damage", 1);
}
