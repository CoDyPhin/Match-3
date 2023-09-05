#include "Game.h"

//std::vector<GameObject*> Game::gameObjects;

Game::Game(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	menu = new Menu(windowWidth, windowHeight);

}

Game::~Game()
{

}

bool Game::canUserInput()
{
	return board == nullptr ? true : !board->isMoving();
}

void Game::processInput(bool r, bool mC, bool mD, int mX, int mY)
{
	isRunning = r;
	mouseClick = mC;
	mouseDrag = mD;
	mouseX = mX;
	mouseY = mY;
	if(canUserInput()) handleInput();
}

void Game::handleInput()
{
	if(board == nullptr)
	{
		for(auto el : menu->buttons)
		{
			if(el->isActive() && el->isColliding(mouseX, mouseY))
			{
				el->setHovered(true);
				if(mouseClick)
				{
					std::string text = el->getText();
					if(text == "Play")
					{
						board = new Board((windowWidth - 660)/2, (windowHeight-660)/2);
						hud = new HUD(10, static_cast<int>(0.2*windowHeight));
						menu->toggle(false);
						return;
					}
					if(text == "Quit") 
					{
						isRunning = false;
						return;
					}
				}
			}
			else el->setHovered(false);
		}
	}
	else {
		std::pair<int, int> coords = board->getPieceIndex(mouseX, mouseY);
		if (mouseClick) // clicked
		{
			if (selectedX == -1 && selectedY == -1) // nothing selected, select
			{
				selectedX = coords.first;
				selectedY = coords.second;
			}
			else // something selected
			{
				if (selectedX == coords.first && selectedY == coords.second) // clicked the same piece, deselect
				{
					selectedX = -1;
					selectedY = -1;
				}
				else // clicked another piece, play
				{
					if (board->areNeighbours(selectedX, selectedY, coords.first, coords.second))
					{
						board->swapPieces(selectedX, selectedY, coords.first, coords.second);
						selectedX = -1;
						selectedY = -1;
					}
					else
					{
						selectedX = coords.first;
						selectedY = coords.second;
					}
				}
			}
		}
		else if (mouseDrag && !wasDragging) // started dragging
		{
			wasDragging = true;
			selectedX = coords.first;
			selectedY = coords.second;

		}
		else if (wasDragging && !mouseDrag) // ended dragging
		{
			wasDragging = false;
			if (!(selectedX == coords.first && selectedY == coords.second))
			{
				if (board->areNeighbours(selectedX, selectedY, coords.first, coords.second))
				{
					if (!board->swapPieces(selectedX, selectedY, coords.first, coords.second))
					{
						selectedY = -1;
						selectedX = -1;
					}
				}
			}
		}
		board->toggleSelected(selectedX, selectedY);
		if (coords.first != -1 && coords.second != -1)
		{
			board->hovering(coords.first, coords.second);
		}
	}
}


void Game::Update()
{
	menu->UpdateMenu();
	if(hud != nullptr) hud->UpdateHUD(board->getScore());
	if(board != nullptr) board->Update();
}