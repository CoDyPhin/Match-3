#include "Piece.h"

Piece::Piece(const char color, const int x, const int y, const int boardX, const int boardY) : GameObject((std::string("Assets/Color-") + color + std::string(".png")).c_str(), boardX, boardY, 1, 1, nullptr, true)
{
	this->color = color;
	Translate(35, 35);
	moveTo(x, y);
}

Piece::~Piece()
{
	
}

void Piece::moveTo(const int x, const int y, const int vx, const int vy)
{
	if(x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
	{
		Translate((x - xIndex) * (getWidth()+5), (y - yIndex) * (getHeight() + 5), vx, vy);
		xIndex = x;
		yIndex = y;
	}
}

