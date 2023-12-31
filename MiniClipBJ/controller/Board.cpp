#include "Board.h"


Board::Board(int startX, int startY, int r, int c, int w, int h) : GameObject(nullptr, startX, startY, w, h)
{
	rows = r >= 2 ? r : 2;
	cols = c >= 2 ? c : 2;
	board.resize(rows, std::vector<Piece*>(cols));
	drawBorders();
	generatePieces();
	selectedSprite = new GameObject("Assets/Extras/selected.png");
	selectedSprite->setActive(false);
	selectedSprite->Scale(0.15f);
	std::set<std::pair<int, int>> var = checkBoard();
	int fill = 0;
	while (!var.empty() || fill > 0)
	{
		removePieces(var);
		applyGravity();
		fill = fillTop();
		var = checkBoard();
	}
	updateChildren();
}

Board::~Board()
{
	for (auto el : borders) delete el;
	for (auto el : board) for (auto el2 : el) delete el2;
}

void Board::updateChildren()
{
	for (auto el : borders) {
		if (el != nullptr) el->Update();
	}
	for (auto el : board) {
		for (auto el2 : el) {
			if (el2 != nullptr) el2->Update();
		}
	}
	selectedSprite->Update();
}

int Board::calculateScore(int pieces)
{
	return pieces <= 3 ? 10 * pieces : calculateScore(pieces - 1) + 10 * (pieces - 2);
}

void Board::addScore(int pieces)
{
	int aux = calculateScore(pieces);
	if(pieces > maxMovePieces) maxMovePieces = pieces;
	score += aux;
}


void Board::Update()
{
	updateChildren();
	fillTop(true);
	applyGravity(pieceVelocity);
	if (!isMoving()) {
		auto const var = checkBoard();
		if (!var.empty()) {
			addScore(var.size());
			removePieces(var);
		}
	}
}

void Board::resetVisited()
{
	for (auto el : board) for (auto el2 : el) 
	{
		if (el2 != nullptr) {
			el2->setVisited(true, false);
			el2->setVisited(false, false);
		}
	}
}

int Board::fillTop(bool wait)
{
	int count = 0;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> dist(1, 5);
	for (int x = 0; x < cols; x++)
	{
		if (board[x][0] == nullptr)
		{
			if(wait)
			{
				auto aux = new Piece(std::to_string(dist(generator))[0], x, 0, xPos, yPos);
				bool spawn = true;
				for (int y = 1; y < rows; y++)
				{
					if(board[x][y] != nullptr && aux->isColliding(board[x][y]))
					{
						spawn = false;
						break;
					}
				}
				if (spawn) {
					board[x][0] = aux;
					count++;
				}
				else delete aux;
			}
			else
			{
				board[x][0] = new Piece(std::to_string(dist(generator))[0], x, 0, xPos, yPos);
				count++;
			}
		}
	}
	return count;
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
		}
	}
}

int Board::dfs(int x, int y, char const color, bool const vertical)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols) return 0;
	if (board[x][y]==nullptr || board[x][y]->getColor() != color) return 0;
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
			if(board[row][col] == nullptr) continue;
			if (!board[row][col]->wasVisited(true))
			{
				int const vertical = dfs(row, col, board[row][col]->getColor(), true);
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

	return result;
}

void Board::removePieces(std::set<std::pair<int, int>> const& pieces)
{
	for (auto const el : pieces)
	{
		delete board[el.first][el.second];
		board[el.first][el.second] = nullptr;
	}
}

void Board::applyGravity(int velocity)
{
	for (int x = cols - 1; x >= 0; x--)
	{
		for (int y = rows - 1; y >= 0; y--)
		{
			if (board[x][y] == nullptr)
			{
				for (int i = y - 1; i >= 0; i--)
				{
					if (board[x][i] != nullptr)
					{
						board[x][i]->moveTo(x,y,0,velocity);
						board[x][y] = board[x][i];
						board[x][i] = nullptr;
						break;
					}
				}
			}
		}
	}
}

void Board::toggleSelected(int x, int y)
{
	int width = -1, height = -1;

	for(int i = 0; i < cols; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			if(board[i][j] != nullptr)
			{
				width = board[i][j]->getWidth();
				height = board[i][j]->getHeight();
				break;
			}
		}
		if(width != -1 && height != -1) break;
	}
	if(x == -1 || y == -1)
	{
		selectedSprite->setActive(false);
	}
	else {
		selectedSprite->setPosition(32 + xPos + x * (width + 5), 32 + yPos + y * (height + 5));
		selectedSprite->setActive(true);
	}
}


std::pair<int, int> Board::getPieceIndex(int xpos, int ypos)
{
	std::pair<int, int> result = std::make_pair(-1, -1);
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			if (board[x][y] != nullptr && board[x][y]->isColliding(xpos, ypos))
			{
				result = std::make_pair(x, y);
				break;
			}
		}
	}
	return result;
}

bool Board::areNeighbours(int x1, int y1, int x2, int y2)
{
	return x1 >= 0 && x2 >= 0 && 
		y1 >= 0 && y2 >= 0 && 
		x1 < rows && x2 < rows && 
		y1 < cols && y2 < cols &&
		(abs(x1 - x2) + abs(y1 - y2) == 1);

}


bool Board::swapPieces(int x1, int y1, int x2, int y2)
{
	Piece* piece1 = board[x1][y1];
	Piece* piece2 = board[x2][y2];

	board[x1][y1] = piece2;
	board[x2][y2] = piece1;
	piece1->moveTo(x2, y2);
	piece2->moveTo(x1, y1);
	if(checkBoard().empty())
	{
		board[x1][y1] = piece1;
		board[x2][y2] = piece2;
		piece1->moveTo(x1, y1, pieceVelocity, pieceVelocity);
		piece2->moveTo(x2, y2, pieceVelocity, pieceVelocity);
		return true;
	}
	return false;
}

bool Board::isMoving()
{
	for (auto pieces : board)
	{
		for (auto piece : pieces)
		{
			if (piece == nullptr || piece->getXVel() != 0 || piece->getYVel() != 0)
			{
				return true;
			}
		}
	}
	return false;
}

void Board::hovering(int x, int y)
{
	if(x >= 0 && y >= 0) board[x][y]->setHovered(true);
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
					borders.emplace_back(auxObj);
				}
				else if (col > 0 && col < cols-1)
				{
					auxObj = new GameObject("Assets/Extras/horizontal.png", xPos, yPos);
					auxObj->Scale(0.17f);
					sepSize = auxObj->getWidth(); // Assuming all separators will be same size
					auxObj->Translate(cornerSize + (col-1) * sepSize, 0);
					borders.emplace_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/topright.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, 0);
					borders.emplace_back(auxObj);
				}
			}
			else if (row == rows-1)
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/botleft.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(0, cornerSize + (row-1) * sepSize);
					borders.emplace_back(auxObj);
				}
				else if (col > 0 && col < cols-1)
				{
					auxObj = new GameObject("Assets/Extras/horizontal.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, cornerSize*1.8 + (row-1) * sepSize);
					borders.emplace_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/botright.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(cornerSize + (col-1) * sepSize, cornerSize + (row-1) * sepSize);
					borders.emplace_back(auxObj);
				}
			}
			else
			{
				if (col == 0)
				{
					auxObj = new GameObject("Assets/Extras/vertical.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(0, cornerSize + (row-1) * sepSize);
					borders.emplace_back(auxObj);
				}
				else if (col == cols - 1)
				{
					auxObj = new GameObject("Assets/Extras/vertical.png", xPos, yPos);
					auxObj->Scale(0.17f);
					auxObj->Translate(1.8*cornerSize + (col-1) * sepSize, cornerSize + (row-1) * sepSize);
					borders.emplace_back(auxObj);
				}
			}
		}
	}
}


