#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Damage(unsigned int damage)
{
	HP -= damage;

	if (HP <= 0) Destroyed = true;
}
