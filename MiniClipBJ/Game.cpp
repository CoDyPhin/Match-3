#include "Game.h"

//std::vector<GameObject*> Game::gameObjects;

Game::Game(int rows, int cols)
{
	board = new Board(20, 20, rows, cols);
}

Game::~Game()
{

}

bool Game::canUserInput()
{
	return !board->isMoving();
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

	std::pair<int, int> coords = board->getPieceIndex(mouseX, mouseY);
	if(mouseClick) // clicked
	{
		if(selectedX == -1 && selectedY == -1) // nothing selected, select
		{
			selectedX = coords.first;
			selectedY = coords.second;
		}
		else // something selected
		{
			if(selectedX == coords.first && selectedY == coords.second) // clicked the same piece, deselect
			{
				selectedX = -1;
				selectedY = -1;
			}
			else // clicked another piece, play
			{
				if(board->areNeighbours(selectedX, selectedY, coords.first, coords.second))
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
	else if(wasDragging && !mouseDrag) // ended dragging
	{
		wasDragging = false;
		if(!(selectedX == coords.first && selectedY == coords.second))
		{
			if (board->areNeighbours(selectedX, selectedY, coords.first, coords.second))
			{
				if(!board->swapPieces(selectedX, selectedY, coords.first, coords.second))
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


void Game::Update()
{
	board->Update();
}