#include "Board.h"


Board::Board(int startX, int startY, uint8_t r, uint8_t c, int w, int h) : GameObject(nullptr, startX, startY, w, h)
{
	rows = r >= 2 ? r : 2;
	cols = c >= 2 ? c : 2;
	board.resize(rows, std::vector<Piece*>(cols));
	drawBorders();
	generatePieces();
}

Board::~Board()
{

}	

void Board::generatePieces()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> dist(1, 5);
	Piece* auxPiece = nullptr;
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			auxPiece = new Piece(std::to_string(dist(generator))[0], x, y, xPos, yPos);
			board[x][y] = auxPiece;
			Game::gameObjects.push_back(auxPiece);
		}
	}
}

void Board::drawBorders()
{
	GameObject* auxObj = nullptr;
	int cornerSize, sepSize;

	for (uint8_t row = 0; row < rows; row++)
	{
		for (uint8_t col = 0; col < cols; col++)
		{
			if (row == 0)
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/topleft.png", xPos, yPos);
					auxObj->Scale(0.17f);
					cornerSize = auxObj->getWidth(); // Assuming all corners will be same size and squares
					Game::gameObjects.push_back(auxObj);
				}
				else if (col > 0 && col < cols-1)
				{
					auxObj = new GameObject("Assets/Extras/horizontal.png", xPos, yPos);
					auxObj->Scale(0.17f);
					sepSize = auxObj->getWidth(); // Assuming all separators will be same size
					auxObj->Translate(cornerSize + (col-1) * sepSize, 0);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/topright.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, 0);
					Game::gameObjects.push_back(auxObj);
				}
			}
			else if (row == rows-1)
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/botleft.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(0, cornerSize + (row-1) * sepSize);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col > 0 && col < cols-1)
				{
					auxObj = new GameObject("Assets/Extras/horizontal.png", xPos, yPos); // wrong
					auxObj->Scale(0.17f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, cornerSize*1.8 + (row-1) * sepSize);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/botright.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, cornerSize + (row-1) * sepSize);
					Game::gameObjects.push_back(auxObj);
				}
			}
			else
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/vertical.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(0, cornerSize + (row-1) * sepSize);
					Game::gameObjects.push_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/vertical.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(1.8*cornerSize + (col-1) * sepSize, cornerSize + (row-1) * sepSize);
					Game::gameObjects.push_back(auxObj);
				}
			}
		}
	}
	
}
