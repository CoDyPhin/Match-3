#include "Piece.h"

Piece::Piece(const char color, const int x, const int y, const int boardX, const int boardY) : GameObject((std::string("Assets/Color-") + color + std::string(".png")).c_str(), boardX, boardY)
{
	this->color = color;
	Translate(50, 50);
	moveTo(x, y);
}

Piece::~Piece()
{
	
}

void Piece::moveTo(const int x, const int y)
{
	if(x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
	{
		Translate(abs(xIndex-x) * getWidth(), abs(yIndex-y) * getHeight()); // TODO: change to setPosition instead of Translate
		xIndex = x;
		yIndex = y;
	}
}

