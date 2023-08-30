#include "Board.h"

Board::Board(int startX, int startY, size_t r, size_t c, int w, int h) : GameObject(nullptr, startX, startY, w, h)
{
	rows = r >= 2 ? r : 2;
	cols = c >= 2 ? c : 2;
	board.resize(rows, std::vector<GameObject>(cols));
	drawBorders();
}

Board::~Board()
{

}	

void Board::drawBorders()
{
	GameObject* auxObj = nullptr;
	int cornerSize, sepSize;

	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			if (row == 0)
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/topleft.png", xPos, yPos);
					auxObj->Scale(0.15f);
					cornerSize = auxObj->getWidth(); // Assuming all corners will be same size and squares
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col > 0 && col < cols-1)
				{
					auxObj = new GameObject("Assets/Extras/horizontal.png", xPos, yPos);
					auxObj->Scale(0.15f);
					sepSize = auxObj->getWidth(); // Assuming all separators will be same size
					auxObj->Translate(cornerSize + (col-1) * sepSize, 0);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/topright.png", xPos, yPos);
					auxObj->Scale(0.15f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, 0);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
			}
			else if (row == rows-1)
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/botleft.png", xPos, yPos);
					auxObj->Scale(0.15f);
					auxObj->Translate(0, cornerSize + (row-1) * sepSize);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col > 0 && col < cols-1)
				{
					auxObj = new GameObject("Assets/Extras/horizontal.png", xPos, yPos); // wrong
					auxObj->Scale(0.15f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, cornerSize*1.8 + (row-1) * sepSize);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/botright.png", xPos, yPos);
					auxObj->Scale(0.15f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, cornerSize + (row-1) * sepSize);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
			}
			else
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/vertical.png", xPos, yPos);
					auxObj->Scale(0.15f);
					auxObj->Translate(0, cornerSize + (row-1) * sepSize);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/vertical.png", xPos, yPos);
					auxObj->Scale(0.15f);
					auxObj->Translate(1.8*cornerSize + (col-1) * sepSize, cornerSize + (row-1) * sepSize);
					borders.push_back(auxObj);
					Game::gameObjects.push_back(auxObj);
				}
			}
		}
	}
	
}
