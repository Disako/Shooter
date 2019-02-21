#include "Enemy.h"
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}


struct Position {

	std::string State;
	int X;
	int Y;
	std::string getState() const { return State; }
	void setState(std::string state) { State = state; }
	int getX() const { return X; }
	void setX(int x) { X = x; }
	int getY() const { return Y; }
	void setY(int y) { Y = y; }
};

Enemy::Enemy(Graphics* graphics, std::string type, std::string initialState)
{
	lua_State* L = luaL_newstate();
	if (luaL_dofile(L, "Definitions\\Enemies.lua"))
	{
		auto error = lua_tostring(L, -1);
		fprintf(stderr, "luaL_dofile failed: %s\n", error);
	}
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);
	
	luabridge::getGlobalNamespace(L)
		.beginClass<Position>("position")
			.addProperty("x", &Position::getX, &Position::setX)
			.addProperty("y", &Position::getY, &Position::setY)
			.addProperty("state", &Position::getState, &Position::setState);
	
	luabridge::LuaRef ref = luabridge::getGlobal(L, type.data());
	
	HP = ref["hp"];

	SetCollision(ref["collision"]);

	Image = graphics->LoadImage(ref["image"]);

	State = initialState;

	Movement = ref["movement"];

	GameObject::Initialise(graphics);
}

int const Enemy::GetX()
{
	return Location.x;
}

void const Enemy::SetX(int x)
{
	Location.x = x;
}

int const Enemy::GetY()
{
	return Location.y;
}

void Enemy::SetY(int y)
{
	Location.y = y;
}

char* const Enemy::GetState()
{
	return State.data();
}

void Enemy::SetState(char* state)
{
	State = state;
}

void Enemy::DoUpdate(GameState * state)
{
	Position position;
	position.X = Location.x;
	position.Y = Location.y;
	position.State = State;

	position = Movement(position);

	Location.x = position.X;
	Location.y = position.Y;
	State = position.State;

	if (IsOutOfBounds(state))
	{
		Destroyed = true;
	}
}

Enemy::~Enemy()
{
}

SDL_Surface * Enemy::GetCurrentImage()
{
	return Image;
}

void Enemy::Damage(unsigned int damage)
{
	HP -= damage;

	if (HP <= 0) Destroyed = true;
}
