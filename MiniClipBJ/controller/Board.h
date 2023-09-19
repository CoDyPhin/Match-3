#pragma once
#include "../model/Piece.h"

class Board: public GameObject
{
public:
	Board(int startX = 0, int startY = 0, int r = 8, int c = 8, int w = 1, int h = 1);
	~Board();
	void Update();
	int cornerSize, sepSize;
	std::set<std::pair<int, int>> checkBoard();
	void applyGravity(int velocity = 0);

	std::pair<int, int> getPieceIndex(int xpos, int ypos);
	bool areNeighbours(int x1, int y1, int x2, int y2);
	bool swapPieces(int x1, int y1, int x2, int y2);
	bool isMoving();
	void toggleSelected(int x, int y);

	int getScore() { return score; }
	int getMaxMovePieces() { return maxMovePieces; }

	void hovering(int x, int y);

private:
	int rows, cols, pieceVelocity = 5;
	std::vector<GameObject*> borders;
	std::vector<std::vector<Piece*>> board;

	GameObject* selectedSprite;

	int score = 0, maxMovePieces = 0;

	void removePieces(std::set<std::pair<int, int>> const& pieces);
	void drawBorders();
	void generatePieces();

	void updateChildren();
	int calculateScore(int pieces);
	void addScore(int pieces);

	int fillTop(bool wait = false);

	void resetVisited();

	int dfs(int x, int y, char color, bool vertical);
};

