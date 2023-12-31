#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
	void RenderBackground();
	void Display();
	void Clean();

	bool getIsRunning() { return isRunning; }
	int getMouseX() { return mouseX; }
	int getMouseY() { return mouseY; }
	bool mouseIsDragging() { return mouseDrag; }
	bool buttonWasClicked() { return buttonClicked; }
	void consumeClick() { buttonClicked = false; }

	uint8_t static getSpeedTime() { return speedTime; }

	int getWindowWidth() { return windowWidth; }
	int getWindowHeight() { return windowHeight; }

	static SDL_Renderer* renderer;

private:
	bool isRunning = false;
	int windowWidth = 1024, windowHeight = 768;
	int mouseX = 0, mouseY = 0;
	static const uint8_t speedTime = 10; //ms
	bool mouseClick = false, mouseDrag = false, buttonClicked = false;
	SDL_Window* window = nullptr;
	SDL_Texture* bgTexture = nullptr;
	void display_SDL_Error_info(const char* failedFunction);
};

