#include "Game.h"

int main(int argc, char* argv[]) {
	Game* game = nullptr;
	game = new Game();


	// TODO: ADD CRUD FOR GAME SETTINGS
	game->Init();


	while(game->getIsRunning())
	{
		game->handleEvents();
		game->Update();
		game->Render();
	}	

	game->Clean();

	return 0;
}