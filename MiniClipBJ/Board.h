#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Piece.h"


class Board: public GameObject
{
public:
	Board(int startX = 0, int startY = 0, int r = 8, int c = 8, int w = 1, int h = 1);
	~Board();
	int cornerSize, sepSize;
	std::set<std::pair<int, int>> checkBoard();

private:
	int rows, cols;
	std::vector<std::vector<Piece*>> board;
	void drawBorders();
	void generatePieces();

	void resetVisited();

	int dfs(int x, int y, char color, bool vertical);
};

