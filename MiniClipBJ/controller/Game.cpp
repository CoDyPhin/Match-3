#include "Game.h"


Game::Game(int windowWidth, int windowHeight, SaveFiles* file)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->file = file;
	level = file->getLevel();
	menu = new Menu(windowWidth, windowHeight, file->getHighScore1(), file->getHighScore2(), file->getHighScore5(), level);
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


void Game::retrieveLevelGoals()
{
	goalScore = 0;
	goalTime = 0;
	oneMovePieces = 0;
	chainScore = 0;
	level = level > 10? level % 10 : level;
	switch (level)
	{
	case 1:
		goalScore = 500;
		break;
	case 2:
		goalScore = 500;
		goalTime = 1;
		break;
	case 3:
		oneMovePieces = 4;
		break;
	case 4:
		chainScore = 200;
		break;
	case 5:
		oneMovePieces = 4;
		goalTime = 2;
		break;
	case 6:
		chainScore = 200;
		goalTime = 2;
		break;
	case 7:
		goalScore = 1000;
		goalTime = 1;
		break;
	case 8:
		goalScore = 2000;
		goalTime = 1;
		break;
	case 9:
		oneMovePieces = 6;
		break;
	case 10:
		chainScore = 300;
		break;
	default:
		break;
	}
}



void Game::startGame(unsigned int menuValue, unsigned gameMode, int time)
{
	delete board;
	delete hud;
	board = nullptr;
	hud = nullptr;
	chainScore = 0;
	oneMovePieces = 0;
	goalScore = 0;
	goalTime = 0;
	scoreBeforeInput = 0;
	highestChainScore = 0;
	menu->getRetry()->setNextMenu(menuValue);
	this->gameMode = gameMode;
	if(gameMode == 2)
	{
		retrieveLevelGoals();
		std::stringstream ss;
		ss << "Level " << level << '\n' << '\n' << '\n' << "Goals" << '\n' << '\n' << '\n';
		if(goalScore > 0) ss << "Total Score" << '\n' << "Over " << goalScore << '\n' << '\n';
		if (goalTime > 0) ss << "Under " << goalTime << " minute";
		if (goalTime > 1) ss << "s";
		if(goalTime > 0) ss << '\n' << '\n';
		if (oneMovePieces > 0) ss << "Break " << oneMovePieces << " pieces" << '\n' << "at once" << '\n' << '\n';
		if(chainScore > 0) ss << chainScore << " chain" << '\n' << "reaction points";
		menu->updateLevelGoals(ss.str());
	}
	if(gameMode == 1) goalTime = time;
	board = new Board((windowWidth - 660) / 2, (windowHeight - 660) / 2);
	hud = new HUD(10, 50, 60*goalTime);
}

void Game::handleInput()
{

	for(Button* el : menu->buttons)
	{
		if(el->isColliding(mouseX, mouseY))
		{
			el->setHovered(true);
			if(mouseClick)
			{
				std::string text = el->getText();
				if (text == "Quit")
				{
					isRunning = false;
					return;
				}
				unsigned int nextMenu = el->getNextMenu();
				menu->setCurrentMenu(nextMenu);
				if (nextMenu == 21)
				{
					startGame(nextMenu);
				}
				if(nextMenu > 30 && nextMenu < 34)
				{
					startGame(nextMenu,1, nextMenu == 33 ? 5 : nextMenu - 30);
				}
				if(nextMenu == 41)
				{
					startGame(nextMenu,2);
				}
				break;
			}
		}
		else el->setHovered(false);
	}

	if(board != nullptr){
		int score = board->getScore();
		if (scoreBeforeInput != score)
		{
			int aux = score - scoreBeforeInput;
			if(aux > highestChainScore) highestChainScore = aux;
			scoreBeforeInput = score;
		}
			
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


bool Game::checkGameOver(int score)
{
	switch (gameMode)
	{
	case 0:
		break;
	case 1:
		if (hud->isTimeOver())
		{
			switch (goalTime)
			{
			case 1:
				menu->setScore1(score);
				menu->setCurrentMenu(101);
				break;
			case 2:
				menu->setScore2(score);
				menu->setCurrentMenu(102);
				break;
			case 5:
				menu->setScore5(score);
				menu->setCurrentMenu(103);
				break;
			default:
				break;
			}
			file->setHighScores(menu->getScore1(), menu->getScore2(), menu->getScore5());
			return true;
		}
		break;
	case 2:
		if((score > goalScore) && (!hud->isTimeOver()) && (highestChainScore >= chainScore) && (board->getMaxMovePieces() >= oneMovePieces))
		{
			level++;
			level = level > 10 ? level % 10 : level;
			file->setLevel(level);
			menu->setLevel(level);
			menu->setCurrentMenu(23);
			return true;
		}
		if(hud->isTimeOver())
		{
			menu->setCurrentMenu(202);
			return true;
		}
		break;
	default:
		isRunning = false;
	}
	return false;
}

void Game::Update()
{
	menu->UpdateMenu();
	if (board != nullptr && hud != nullptr) {
		board->Update();
		int score = board->getScore();
		hud->UpdateHUD(score);
		if(checkGameOver(score) || menu->getCurrentMenu() == 1)
		{
			delete board;
			delete hud;
			board = nullptr;
			hud = nullptr;
		}
	}
}