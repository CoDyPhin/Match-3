#include "./view/Renderer.h"
#include "./controller/Game.h"
#include "./utils/SaveFiles.h"

int main(int argc, char* argv[]) {

	SaveFiles* file = new SaveFiles();

	Renderer* renderer = new Renderer(file->getDisplayMode(),file->getWidth(),file->getHeight());

	Game* game = new Game(renderer->getWindowWidth(), renderer->getWindowHeight(), file);

	while(renderer->getIsRunning() && game->getIsRunning())
	{
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