#pragma once
#include "Piece.h"

class Board: public GameObject
{
public:
	Board(int startX = 0, int startY = 0, int r = 8, int c = 8, int w = 1, int h = 1);
	~Board();
	void Update();
	int cornerSize, sepSize;
	std::set<std::pair<int, int>> checkBoard();
	void applyGravity();

private:
	int rows, cols;
	std::vector<GameObject*> borders;
	std::vector<std::vector<Piece*>> board;
	void removePieces(std::set<std::pair<int, int>> const& pieces);
	void drawBorders();
	void generatePieces();

	void resetVisited();

	int dfs(int x, int y, char color, bool vertical);
};

