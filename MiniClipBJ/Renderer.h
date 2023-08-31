#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>


#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768
#define DISPLAY_MODE_WINDOWED 0
#define DISPLAY_MODE_FULLSCREEN 1
#define DISPLAY_MODE_FULLSCREEN_NATIVE 2
#define DISPLAY_MODE_BORDERLESS 3


class Renderer
{
public:
	Renderer(uint8_t displayMode = DISPLAY_MODE_WINDOWED, int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED);
	~Renderer();

	void handleEvents();
	//void Update();
	void RenderBackground();
	void Display();
	void Clean();

	bool getIsRunning() { return isRunning; }

	static SDL_Renderer* renderer;
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Texture* bgTexture = nullptr;
	void display_SDL_Error_info(const char* failedFunction);
};

