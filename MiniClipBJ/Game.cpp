#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::Init(uint8_t displayMode, int width, int height, int xpos, int ypos)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		switch (displayMode)
		{
			// default window modes
			case DISPLAY_MODE_WINDOWED:
				flags = SDL_WINDOW_SHOWN;
				break;
			case DISPLAY_MODE_FULLSCREEN:
				flags = SDL_WINDOW_FULLSCREEN;
				break;
			case DISPLAY_MODE_FULLSCREEN_NATIVE:
				flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
				break;
			case DISPLAY_MODE_BORDERLESS:
				flags = SDL_WINDOW_BORDERLESS;
				break;
			default:
				flags = SDL_WINDOW_SHOWN;
				break;
		}
		window = SDL_CreateWindow("MiniClip Match-3", xpos, ypos, width, height, flags);
		// check if window is null
		if(window)
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
			// check if renderer is null
			if(renderer)
			{
				isRunning = true;
				if (SDL_SetRenderDrawColor(renderer, 153, 196, 224, 255) != 0) display_SDL_Error_info("SDL_SetRenderDrawColor"); //Light Blue
			}
			else
			{
				display_SDL_Error_info("SDL_CreateRenderer");
			}
		}
		else
		{
			display_SDL_Error_info("SDL_CreateWindow");
		}
	}
	else
	{
		display_SDL_Error_info("SDL_Init");
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::Update()
{

}

void Game::Render()
{
	if (SDL_RenderClear(renderer) != 0) display_SDL_Error_info("SDL_RenderClear");
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}



void Game::display_SDL_Error_info(const char* failedFunction)
{
		std::cout << failedFunction << " failed. Error: " << SDL_GetError() << std::endl;
		isRunning = false;
}
