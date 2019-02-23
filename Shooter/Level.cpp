#include "Level.h"
#include <sstream>
#include "Enemy.h"

Level::Level(lua_State* L, std::string levelName)
{

	this->L = L;
	auto ref = LuaLoadedObject::GetRef(L, levelName);

	if (ref.length() == 0)
	{
		std::stringstream error;
		error << levelName << "Must have at least 1 action";
		throw std::runtime_error(error.str());
	}

	for (int i = 1; i <= ref.length(); i++)
	{
		Events.push_back(ref[i]);
	}
}


Level::~Level()
{
}

Level* Level::DoUpdate(GameState* state, Resources* resources) 
{
	Level* nextLevel = this;

	while (Wait == 0)
	{
		if (Index >= Events.size()) Index = 0;

		auto action = GetString(Events[Index], "action", "none");

		if (action == "spawn")
		{
			auto enemy = new Enemy(resources, L, GetString(Events[Index], "enemy", "blank"), GetString(Events[Index], "state", "None"));
			enemy->Location.x = GetInt(Events[Index], "location", 1, 0);
			enemy->Location.y = GetInt(Events[Index], "location", 2, 0);

			state->GameObjects.push_back(enemy);
		}
		else if (action == "wait")
		{
			Wait = GetInt(Events[Index], "frames", 1);
		}
		else if (action == "level")
		{
			nextLevel = new Level(L, GetString(Events[Index], "level", "blank"));
		}
		else
		{
			std::stringstream error;
			error << "Unknown level action: " << action;
			throw std::runtime_error(error.str());
		}

		Index++;
	}

	Wait--;

	return nextLevel;
}