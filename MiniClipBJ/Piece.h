#pragma once
#include "GameObject.h"

class Piece : public GameObject
{
public:
	Piece(char color, int x, int y, int boardX = 0, int boardY = 0);
	~Piece();

	int getXIndex() { return xIndex; }
	int getYIndex() { return yIndex; }
	char getColor() { return color; }

	void moveTo(int x, int y);
	/*void moveLeft() { moveTo(xIndex - 1, yIndex); }
	void moveRight() { moveTo(xIndex + 1, yIndex); }
	void moveUp() { moveTo(xIndex, yIndex - 1); }
	void moveDown() { moveTo(xIndex, yIndex + 1); }*/

	void setVisited(bool vertical, bool visited) { if (vertical) vVisited = visited; else hVisited = visited; }
	bool wasVisited(bool vertical) { return vertical ? vVisited : hVisited; }

private:
	char color;
	int xIndex, yIndex;

	bool vVisited = false;
	bool hVisited = false;
};

