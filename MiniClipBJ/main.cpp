#include "Renderer.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	// TODO: ADD CRUD FOR GAME SETTINGS

	Renderer* renderer = new Renderer();

	Game* game = new Game();

	while(renderer->getIsRunning())
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(25));
		renderer->handleEvents();
		renderer->RenderBackground();
		game->Update();
		renderer->Display();
	}

	renderer->Clean();
	return 0;
}