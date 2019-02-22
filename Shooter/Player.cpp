#include "Player.h"
#include "SDL.h"
#include "Graphics.h"
#include "Enemy.h"
#include <string>
#include <tuple>
#include "PlayerShot.h"
#include <sstream>

Player::Player(Graphics* graphics) : Player(graphics, GameObject::SetupLua("Definitions\\Player.lua", "player"))
{
}

Player::Player(Graphics* graphics, std::tuple<lua_State*, luabridge::LuaRef> luaRef) : GameObject(graphics, luaRef)
{
	Initialise(graphics, std::get<0>(luaRef), std::get<1>(luaRef));
}

Player::~Player()
{
}

void Player::DoUpdate(GameState* state)
{
	const int maxSpeed = 5;

	int up = 0, left = 0;

	if (state->Keys[SDLK_UP] || state->Keys[SDLK_w]) up++;
	if (Location.y > state->ScreenHeight - Location.h * 9 / 8) up++;
	if (state->Keys[SDLK_DOWN] || state->Keys[SDLK_s]) up--;
	if (Location.y < Location.h / 8) up--;

	if (state->Keys[SDLK_LEFT] || state->Keys[SDLK_a]) left++;
	if (Location.x > state->ScreenWidth - Location.w * 9 / 8) left++;
	if (state->Keys[SDLK_RIGHT] || state->Keys[SDLK_d]) left--;
	if (Location.x < Location.w / 8) left--;

	auto firing = (state->Keys[SDLK_SPACE] || state->Keys[SDLK_RETURN]);
	for (unsigned int i = 0; i < Weapons.size(); i++)
	{
		if (firing && Weapons[i].RemainingReload == 0)
		{
			auto shot = new PlayerShot(Weapons[i].GraphicsStore, Weapons[i].L, Weapons[i].Ref, Weapons[i].InitialState);

			shot->Location.x = Location.x + Weapons[i].PositionX;
			shot->Location.y = Location.y + Weapons[i].PositionY;

			state->GameObjects.push_back(shot);

			Weapons[i].RemainingReload = Weapons[i].Reload;
		}
		else if (Weapons[i].RemainingReload > 0)
		{
			Weapons[i].RemainingReload--;
		}
	}
	/*if ((state->Keys[SDLK_SPACE] || state->Keys[SDLK_RETURN]) && Reload == 0)
	{
		BasicBullet* bullet = new BasicBullet(GraphicsStore);
		bullet->Location.x = Location.x + Location.w / 2 - bullet->Location.w / 2;
		bullet->Location.y = Location.y;
		state->GameObjects.push_back(bullet);
		Reload = 10;
	}
	else if (Reload > 0)
	{
		Reload--;
	}*/

	if (up > 0)
	{
		Speed.y--;
	}
	else if (up < 0)
	{
		Speed.y++;
	}
	else if (Speed.y < 0)
	{
		Speed.y++;
	}
	else if (Speed.y > 0)
	{
		Speed.y--;
	}

	if (left > 0)
	{
		Speed.x--;
	}
	else if (left < 0)
	{
		Speed.x++;
	}
	else if (Speed.x < 0)
	{
		Speed.x++;
	}
	else if (Speed.x > 0)
	{
		Speed.x--;
	}

	if (Speed.x > maxSpeed) Speed.x = maxSpeed;
	else if (Speed.x < -maxSpeed) Speed.x = -maxSpeed;
	if (Speed.y > maxSpeed) Speed.y = maxSpeed;
	else if (Speed.y < -maxSpeed) Speed.y = -maxSpeed;

	Location.x += Speed.x;
	Location.y += Speed.y;

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(state->GameObjects[i]);
		if (enemy)
		{
			if (CheckCollision(enemy))
			{
				enemy->Damage(10);
				Destroyed = true;
			}
		}
	}
}

void Player::Initialise(Graphics * graphics, lua_State* L, luabridge::LuaRef ref)
{
	auto weapons = ref["weapons"];
	Weapons.clear();

	if (weapons.isNil()) return;
	if (!weapons.isTable())
	{
		throw std::runtime_error("Invalid value for weapons, expects list");
	}
	for (int i = 1; i <= weapons.length(); i++)
	{
		auto weaponRef = weapons[i];
		if (!weaponRef.isTable())
		{
			throw std::runtime_error("Invalid value for weapons, expects table");
		}
		Weapon weapon;
		std::string weaponTypeString = GetString(weaponRef, "identifier", "blank");
		weapon.Ref = luabridge::getGlobal(L, weaponTypeString.data());
		if (weapon.Ref.isNil())
		{
			std::stringstream error;
			error << "Could not find weapon named " << weaponTypeString;
			throw std::runtime_error(error.str());
		}
		weapon.Reload = GetInt(weaponRef, "reload", 0);
		weapon.InitialState = GetString(weaponRef, "initialState", "none");
		weapon.PositionX = GetInt(weaponRef, "position", 1, 0);
		weapon.PositionY = GetInt(weaponRef, "position", 2, 0);
		weapon.L = L;
		weapon.RemainingReload = 0;
		weapon.GraphicsStore = graphics;

		Weapons.push_back(weapon);
	}
}
