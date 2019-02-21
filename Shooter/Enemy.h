#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "..\LuaBridge\Source\LuaBridge\LuaBridge.h"
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy(Graphics* graphics, std::string type, std::string initialState);
	~Enemy();
	int HP;
	void Damage(unsigned int damage);
	SDL_Surface* Image;
	void DoUpdate(GameState* state) override;
	std::string State;
protected:
	SDL_Surface* GetCurrentImage() override;
private:
	luabridge::LuaRef Movement = nullptr;
	void SetState(char* state);
	char* const GetState();
	void const SetX(int state);
	int const GetX();
	void SetY(int state);
	int const GetY();
};

