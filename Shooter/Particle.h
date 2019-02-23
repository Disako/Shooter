#pragma once
#include "GameObject.h"
class Particle :
	public GameObject
{
public:
	Particle(Resources* resources, luabridge::LuaRef ref, int parentX, int parentY);
	~Particle();
	void DoUpdate(GameState* state) override;
private:
	void Initialise(Resources* resources, luabridge::LuaRef ref, int parentX, int parentY);
	int Angle;
	int CenterX, CenterY;
	int TTL;
	int Age;
	int Speed;
};

