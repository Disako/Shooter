#include "Player.h"
#include "SDL.h"
#include "Resources.h"
#include "Enemy.h"
#include <string>
#include <tuple>
#include "PlayerShot.h"
#include <sstream>
#include "UpgradeShip.h"

Player::Player(Resources* resources, lua_State* L, std::string playerType) : Player(resources, L, GameObject::GetRef(L, playerType))
{
}

Player::Player(Resources* resources, lua_State* L, luabridge::LuaRef ref) : GameObject(resources, ref)
{
	Initialise(resources, L, ref);
}

Player::~Player()
{
}

void Player::DoUpdate(GameState* state)
{
	if (Invincibility > 0)
	{
		Invincibility--;
	}

	if (LastChange > 0) LastChange--;

	if (Frame < (Level - 1) * 4)
	{
		if (LastChange == 0)
		{
			Frame++;
			LastChange = 6;
		}
	}
	else
	{
		Frame = (Level - 1) * 4;
	}

	const int maxSpeed = 5;

	int up = 0, left = 0;

	if (state->Keys[SDL_SCANCODE_UP] || state->Keys[SDL_SCANCODE_W]) up++;
	if (Location.y > state->ScreenHeight - Location.h * 9 / 8) up++;
	if (state->Keys[SDL_SCANCODE_DOWN] || state->Keys[SDL_SCANCODE_S]) up--;
	if (Location.y < Location.h / 8) up--;

	if (state->Keys[SDL_SCANCODE_LEFT] || state->Keys[SDL_SCANCODE_A]) left++;
	if (Location.x > state->ScreenWidth - Location.w * 9 / 8) left++;
	if (state->Keys[SDL_SCANCODE_RIGHT] || state->Keys[SDL_SCANCODE_D]) left--;
	if (Location.x < Location.w / 8) left--;

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

	auto firing = (state->Keys[SDL_SCANCODE_SPACE] || state->Keys[SDL_SCANCODE_RETURN]);
	for (unsigned int i = 0; i < Weapons.size(); i++)
	{
		if (Weapons[i].LastSound > 0) Weapons[i].LastSound--;

		if (firing && Weapons[i].RemainingReload == 0 && Level >= Weapons[i].MinLevel && Level <= Weapons[i].MaxLevel)
		{
			auto shot = new PlayerShot(ResourcesStore, Weapons[i].Ref, Weapons[i].InitialState);

			shot->Location.x = Location.x + Weapons[i].PositionX;
			shot->Location.y = Location.y + Weapons[i].PositionY;

			state->GameObjects.push_back(shot);

			Weapons[i].RemainingReload = Weapons[i].Reload;

			if (Weapons[i].FireSound != nullptr && Weapons[i].LastSound == 0)
			{
				Mix_VolumeChunk(Weapons[i].FireSound, (MIX_MAX_VOLUME * Weapons[i].FireVolume) / 100);
				Mix_PlayChannel(-1, Weapons[i].FireSound, 0);
				Weapons[i].LastSound = Weapons[i].SoundFrequency;
			}
		}
		else if (Weapons[i].RemainingReload > 0)
		{
			Weapons[i].RemainingReload--;
		}
	}

	for (unsigned int i = 0; i < state->GameObjects.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(state->GameObjects[i]);
		if (!Invincibility && enemy)
		{
			if (CheckCollision(enemy))
			{
				enemy->Damage(25);
				if (Level == 1)
				{
					Destroyed = true;
					state->GameOver = true;
				}
				else
				{
					Destroy(state, ResourcesStore);
					SetLevel(Level - 1, true, state);
					Invincibility = 60;
					state->ScoreMultiplier = 1;
				}
			}
		}
		UpgradeShip* upgrade = dynamic_cast<UpgradeShip*>(state->GameObjects[i]);
		if (upgrade)
		{
			if (CheckCollision(upgrade))
			{
				SetLevel(Level + 1, false, state);
				upgrade->Destroyed = true;
			}
		}
	}
}

void Player::SetLevel(int level, bool immediate, GameState* state)
{
	if (level <= MaxLevel)
	{
		Level = level;
		SetCollision(CollisionRefs[level]);
		if (immediate) Frame = (Level - 1) * 4;
	}
	else
	{
		state->ScoreMultiplier++;
	}

}

void Player::Initialise(Resources * resources, lua_State* L, luabridge::LuaRef ref)
{
	MaxLevel = GetInt(ref, "maxLevel", 1);

	CollisionRefs = ref["levelCollision"];

	if (CollisionRefs.isNil())
	{
		throw std::runtime_error("levelCollision is required");
	}
	else if (!CollisionRefs.isTable())
	{
		throw std::runtime_error("Invalid value for levelCollision, expects table");
	}
	else if (CollisionRefs.length() < MaxLevel)
	{
		throw std::runtime_error("Must have as many levelCollision items as the max level");
	}

	auto weapons = ref["weapons"];
	Weapons.clear();
	ResourcesStore = resources;

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
		weapon.Ref = GetRef(L, weaponTypeString.data());
		weapon.Reload = GetInt(weaponRef, "reload", 0);
		weapon.InitialState = GetString(weaponRef, "initialState", "none");
		weapon.PositionX = GetInt(weaponRef, "position", 1, 0);
		weapon.PositionY = GetInt(weaponRef, "position", 2, 0);
		weapon.RemainingReload = 0;
		weapon.MinLevel = GetInt(weaponRef, "minLevel", 1);
		weapon.MaxLevel = GetInt(weaponRef, "maxLevel", MaxLevel);
		weapon.SoundFrequency = GetInt(weaponRef, "soundFrequency", 1);
		auto fireSound = GetString(weaponRef, "fireSound", "");
		if (fireSound != "")
		{
			weapon.FireSound = resources->LoadSound(fireSound);
		}
		else
		{
			weapon.FireSound = nullptr;
		}
		weapon.FireVolume = GetInt(weaponRef, "fireVolume", 100);


		Weapons.push_back(weapon);

		SetLevel(1, true, nullptr);
	}
}
