#include "Particle.h"

Particle::Particle(Resources* resources, luabridge::LuaRef ref, int parentX, int parentY) : 
	GameObject(resources, ref)
{
	Initialise(resources, ref, parentX, parentY);
}

Particle::~Particle()
{
}

void Particle::Initialise(Resources* resources, luabridge::LuaRef ref, int parentX, int parentY)
{
	auto positionAngle = Random(0, 359);
	Angle = Random(0, 359);
	auto radius = Random(GetInt(ref, "positionRadius", 1, 0), GetInt(ref, "positionRadius", 2, 0));
	CenterX = parentX + sin(Rad(positionAngle)) * radius + GetInt(ref, "center", 1, 0);
	CenterY = parentY + cos(Rad(positionAngle)) * radius + GetInt(ref, "center", 2, 0);
	TTL = Random(GetInt(ref, "ttl", 1, 0), GetInt(ref, "ttl", 2, 0));
	Age = 0;
	Speed = Random(GetInt(ref, "speed", 1, 0), GetInt(ref, "speed", 2, 0));
}

void Particle::DoUpdate(GameState* state)
{
	GameObject::DoUpdate(state);

	Location.x = CenterX + sin(Rad(Angle)) * Speed * Age;
	Location.y = CenterY + cos(Rad(Angle)) * Speed * Age;

	Frame = (Age * Frames.size()) / TTL;
	if (Frame >= Frames.size()) Frame = Frames.size() - 1;
	Age++;
	if (Age >= TTL)
	{
		Destroyed = true;
	}
}
