#pragma once
#include "Board.h"

class Game
{
public:
	Game(int rows = 8, int cols = 8);
	~Game();

	void Update();

private:
	Board* board = nullptr;
};

