#include "PlayerShot.h"
#include "Enemy.h"
#include <tuple>

PlayerShot::PlayerShot(Resources* resources, luabridge::LuaRef ref, std::string initialState) : AutoMove(resources, ref, initialState)
{
	Initialise(resources, ref);
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
		if (enemy && !enemy->Immune)
		{
			if (CheckCollision(enemy))
			{
				enemy->Damage(Damage);
				Destroyed = true;
			}
		}
	}
}

void PlayerShot::Initialise(Resources * resources, luabridge::LuaRef ref)
{
	Damage = GetInt(ref, "damage", 1);
}
