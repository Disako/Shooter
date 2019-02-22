#pragma once
#include <string>


struct Position {

	std::string State;
	int X;
	int Y;
	int getX() const { return X; }
	void setX(int x) { X = x; }
	int getY() const { return Y; }
	void setY(int y) { Y = y; }
	std::string getState() const { return State; }
	void setState(std::string state) { State = state; }
};
