#include "PlayerShot.h"
#include "Enemy.h"


PlayerShot::PlayerShot()
{
}


PlayerShot::~PlayerShot()
{
}

void PlayerShot::DoUpdate(GameState * state)
{
	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(state->GameObjects[i]);
		if (enemy)
		{
			if (CheckCollision(enemy))
			{
				enemy->Damage(GetDamage());
				Destroyed = true;
			}
		}
	}

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

unsigned int PlayerShot::GetDamage()
{
	return 0;
}
