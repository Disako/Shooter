#pragma once
#include <string>


struct Position {

	std::string State;
	int X;
	int Y;
	int Frame;
	int Count;
	int getX() const { return X; }
	void setX(int x) { X = x; }
	int getY() const { return Y; }
	void setY(int y) { Y = y; }
	int getFrame() const { return Frame; }
	void setFrame(int frame) { Frame = frame; }
	int getCount() const { return Count; }
	void setCount(int count) { Count = count; }
	std::string getState() const { return State; }
	void setState(std::string state) { State = state; }
};
