#include "Board.h"


Board::Board(int startX, int startY, int r, int c, int w, int h) : GameObject(nullptr, startX, startY, w, h)
{
	rows = r >= 2 ? r : 2;
	cols = c >= 2 ? c : 2;
	board.resize(rows, std::vector<Piece*>(cols));
	drawBorders();
	generatePieces();
	checkBoard();
}

Board::~Board()
{

}

void Board::resetVisited()
{
	for (auto el : board) for (auto el2 : el) 
	{
		el2->setVisited(true, false);
		el2->setVisited(false, false);
	}
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

int Board::dfs(int x, int y, char const color, bool const vertical)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols) return 0;
	if (board[x][y]->getColor() != color) return 0;
	if (!vertical)
	{
		return 1 + dfs(x + 1, y, color, vertical);
	}
	else
	{
		return 1 + dfs(x, y + 1, color, vertical);
	}
}


std::set<std::pair<int, int>> Board::checkBoard()
{
	std::set<std::pair<int, int>> result;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (!board[row][col]->wasVisited(true))
			{
				int const vertical = dfs(row, col, board[row][col]->getColor(), true);
				std::cout << board[row][col]->getColor() << std::endl;
				std::cout << "(i, j) = " << row << " " << col << " vertical = " << vertical << std::endl;
				if (vertical >= 3)
				{
					for (int i = col; i < col + vertical; i++)
					{
						result.insert(std::make_pair(row, i));
					}
				}
				board[row][col]->setVisited(true, false);
			}
			if (!board[row][col]->wasVisited(false))
			{
				int const horizontal = dfs(row, col, board[row][col]->getColor(), false);
				std::cout << "(i, j) = " << row << " " << col << " horizontal = " << horizontal << std::endl;
				if (horizontal >= 3)
				{
					for (int i = row; i < row + horizontal; i++)
					{
						result.insert(std::make_pair(i, col));
					}
				}
				board[row][col]->setVisited(false, false);
			}
		}
	}
	resetVisited();
	// print all the pairs
	for (auto const el : result) std::cout << el.first << " " << el.second << std::endl;

	return result;
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
