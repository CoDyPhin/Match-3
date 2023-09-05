#include "Renderer.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	// TODO: ADD CRUD FOR GAME SAVE FILES

	Renderer* renderer = new Renderer();

	Game* game = new Game(renderer->getWindowWidth(), renderer->getWindowHeight());

	while(renderer->getIsRunning() && game->getIsRunning())
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(25));
		renderer->handleEvents();
		game->processInput(renderer->getIsRunning(), renderer->buttonWasClicked(), renderer->mouseIsDragging(), renderer->getMouseX(), renderer->getMouseY());
		renderer->consumeClick();
		renderer->RenderBackground();
		game->Update();
		renderer->Display();
	}

	renderer->Clean();
	return 0;
}