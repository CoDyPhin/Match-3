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

void Game::receiveInput(bool r, bool mC, bool mD, int mX, int mY)
{
	isRunning = r;
	mouseClick = mC;
	mouseDrag = mD;
	mouseX = mX;
	mouseY = mY;
	if(!canUserInput()) handleInput();
}

void Game::handleInput()
{
	if(mouseClick)
	{
		if(selectedX == -1 && selectedY == -1)
		{
			std::pair<int, int> coords = board->getPieceIndex(mouseX, mouseY);
			//board->toggleSelected(coords.first, coords.second);
			selectedX = coords.first;
			selectedY = coords.second;
			//std::cout << "Selected piece: " << coords.first << ", " << coords.second << std::endl;
		}
		else
		{
			std::pair<int, int> coords = board->getPieceIndex(mouseX, mouseY);
			if(selectedX == coords.first && selectedY == coords.second)
			{
				//std::cout << "De-selected piece: " << coords.first << ", " << coords.second << std::endl;
				selectedX = -1;
				selectedY = -1;
			}
			else
			{
				if(board->areNeighbours(selectedX, selectedY, coords.first, coords.second))
				{
					board->swapPieces(selectedX, selectedY, coords.first, coords.second);
					selectedX = -1;
					selectedY = -1;
				}
				else
				{
					//std::cout << "Selected piece: " << coords.first << ", " << coords.second << std::endl;
					selectedX = coords.first;
					selectedY = coords.second;
				}
			}
		}
	}
	else if (mouseDrag)
	{
		if (!failedMove) {
			std::pair<int, int> coords = board->getPieceIndex(mouseX, mouseY);
			if (selectedX == -1 && selectedY == -1)
			{
				if(!wasDragging)
				{
					selectedX = coords.first;
					selectedY = coords.second;
				}
			}
			else
			{
				if (board->areNeighbours(selectedX, selectedY, coords.first, coords.second))
				{
					failedMove = board->swapPieces(selectedX, selectedY, coords.first, coords.second);
					selectedX = -1;
					selectedY = -1;
				}
			}
			wasDragging = true;
		}
	}
	else
	{
		if(wasDragging)
		{
			wasDragging = false;
			failedMove = false;
			selectedX = -1;
			selectedY = -1;
		}
	}
}


void Game::Update()
{
	board->Update();
}