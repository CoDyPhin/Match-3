#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768
#define DISPLAY_MODE_WINDOWED 0
#define DISPLAY_MODE_FULLSCREEN 1
#define DISPLAY_MODE_FULLSCREEN_NATIVE 2
#define DISPLAY_MODE_BORDERLESS 3

class Game
{
public:
	Game();
	~Game();

	void Init(uint8_t displayMode = DISPLAY_MODE_WINDOWED, int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED);

	void handleEvents();
	void Update();
	void Render();
	void Clean();

	bool getIsRunning() { return isRunning; }

private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* bgTexture = nullptr;
	void display_SDL_Error_info(const char* failedFunction);
};

