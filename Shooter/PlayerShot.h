#pragma once
#include "GameObject.h"
class PlayerShot :
	public GameObject
{
public:
	PlayerShot();
	~PlayerShot();
	virtual void DoUpdate(GameState* state) override;

	virtual unsigned int GetDamage();
};

