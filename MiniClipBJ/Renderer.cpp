#include "Renderer.h"

SDL_Renderer* Renderer::renderer = nullptr;


Renderer::Renderer(uint8_t displayMode, int width, int height, int xpos, int ypos)
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
		if (window)
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
			// check if renderer is null
			if (renderer)
			{
				isRunning = true;
				if (SDL_SetRenderDrawColor(renderer, 153, 196, 224, 255) != 0) display_SDL_Error_info("SDL_SetRenderDrawColor"); //Light Blue
			}
			else display_SDL_Error_info("SDL_CreateRenderer");
		}
		else display_SDL_Error_info("SDL_CreateWindow");

		bgTexture = IMG_LoadTexture(renderer, "Assets/Backdrop13.jpg");
		if (bgTexture == nullptr) display_SDL_Error_info("IMG_LoadTexture");
	}
	else display_SDL_Error_info("SDL_Init");

}

Renderer::~Renderer()
{
	Clean();
}

void Renderer::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
		if (mouseClick)
		{
			mouseDrag = true;
			//std::cout << "Mouse Dragging" << std::endl;
		}
		SDL_GetMouseState(&mouseX, &mouseY);
		//std::cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << std::endl;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouseClick = true;
			//std::cout << "Mouse Clicked" << std::endl;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouseDrag = false;
			buttonClicked = true;
			mouseClick = false;
			//std::cout << "Mouse Released" << std::endl;
		}
		break;
	default:
		break;
	}
}

void Renderer::RenderBackground()
{
	if (SDL_RenderClear(renderer) != 0) display_SDL_Error_info("SDL_RenderClear");

	SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);

}

void Renderer::Display()
{
	SDL_RenderPresent(renderer);
}

void Renderer::Clean()
{
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Renderer::display_SDL_Error_info(const char* failedFunction)
{
	std::cout << failedFunction << " failed. Error: " << SDL_GetError() << std::endl;
	isRunning = false;
}

