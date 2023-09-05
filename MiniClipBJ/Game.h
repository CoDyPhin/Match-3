#pragma once
#include "Board.h"
#include "HUD.h"
#include "Menu.h"

class Game
{
public:
	Game(int windowWidth, int windowHeight);
	~Game();

	void Update();
	void processInput(bool r, bool mC, bool mD, int mX, int mY);
	void handleInput();
	bool getIsRunning() { return isRunning; }

private:
	Board* board = nullptr;
	HUD* hud = nullptr;
	Menu* menu = nullptr;
	int mouseX = 0, mouseY = 0, selectedX = -1, selectedY = -1, windowWidth, windowHeight;
	bool mouseClick = false, mouseDrag = false, isRunning = true, wasDragging = false, failedMove = false;

	bool canUserInput();
};

