#pragma once
#include "GameObject.h"
#include "Game.h"

class Board: public GameObject
{
public:
	Board(int startX = 0, int startY = 0, size_t r = 8, size_t c = 8, int w = 1, int h = 1);
	~Board();

private:
	size_t rows, cols;
	std::vector<std::vector<GameObject>> board;
	std::vector<GameObject*> borders;
	void drawBorders();
};

