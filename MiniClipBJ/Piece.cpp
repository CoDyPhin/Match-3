#include "Piece.h"


Piece::Piece(const char color, const int x, const int y, const int boardX, const int boardY) : GameObject((std::string("Assets/Color-") + color + std::string(".png")).c_str(), boardX, boardY) //adicionar offset
{
	this->color = color;
	Translate(40, 40);
	moveTo(x, y);
}

Piece::~Piece()
{
	
}

void Piece::moveTo(const int x, const int y)
{
	if(x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
	{
		xIndex = x;
		yIndex = y;

		Translate(xIndex * getWidth() + 10, yIndex * getHeight() + 10);
	}
}

