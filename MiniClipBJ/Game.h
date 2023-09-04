#pragma once
#include "Board.h"
#include "HUD.h"

class Game
{
public:
	Game(int windowWidth, int windowHeight, int rows = 8, int cols = 8);
	~Game();

	void Update();
	void processInput(bool r, bool mC, bool mD, int mX, int mY);
	void handleInput();

private:
	Board* board = nullptr;
	HUD* hud = nullptr;
	int mouseX = 0, mouseY = 0, selectedX = -1, selectedY = -1;
	bool mouseClick = false, mouseDrag = false, isRunning = false, wasDragging = false, failedMove = false;

	bool canUserInput();
};

