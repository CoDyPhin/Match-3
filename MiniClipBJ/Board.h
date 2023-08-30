#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Piece.h"


class Board: public GameObject
{
public:
	Board(int startX = 0, int startY = 0, uint8_t r = 8, uint8_t c = 8, int w = 1, int h = 1);
	~Board();
	int cornerSize, sepSize;

private:
	uint8_t rows, cols;
	std::vector<std::vector<Piece*>> board;
	void drawBorders();
	void generatePieces();
};

