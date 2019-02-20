#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();
	int HP;
	void Damage(unsigned int damage);
};

