extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "SDL.h"
#include "GameState.h"
#include "Resources.h"
#include <vector>
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "LuaLoadedObject.h"

#pragma once
class GameObject :
	public LuaLoadedObject
{
public:
	virtual ~GameObject();

	SDL_Rect Location;
	bool Destroyed;

	void Draw(SDL_Surface* screen);
	virtual void DoUpdate(GameState* state);
	bool CheckCollision(GameObject* otherObject);
	void Destroy(GameState* state, Resources* resources);
	int Frame;
protected:
	GameObject(Resources* resources, luabridge::LuaRef ref);
	virtual SDL_Surface* GetCurrentImage();
	bool IsOutOfBounds(GameState* state);
	std::vector<SDL_Rect> Frames;
	double Rad(int degrees);
	int Random(int min, int max);
	void SetCollision(luabridge::LuaRef ref);
private:
	SDL_Surface* Image;
	std::vector<SDL_Rect> Collision;
	void Initialise(Resources* resources, luabridge::LuaRef ref);
	Mix_Chunk* ExplodeSound;
	int ExplodeVolume;
	std::vector<luabridge::LuaRef> ExplodeParticles;
	void SetupExplodeParticles(luabridge::LuaRef ref);
};

