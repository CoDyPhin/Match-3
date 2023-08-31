#include "Game.h"

//std::vector<GameObject*> Game::gameObjects;

Game::Game(int rows, int cols)
{
	board = new Board(20, 20, rows, cols);
}

Game::~Game()
{

}


void Game::Update()
{
	board->Update();
}