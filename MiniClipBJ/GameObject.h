#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <cmath>

class GameObject
{
public:
	GameObject(SDL_Renderer* ren, const char* texturePath = nullptr, int startX = 0, int startY = 0);
	~GameObject();

	void Update();
	void Render();

	void Translate(int x = 0, int y = 0);
	void setPosition(int x = 0, int y = 0);

	void Scale(float factor = 1.0f);
	void Scale(float xFactor = 1.0f, float yFactor = 1.0f);

	float getXScale() { return xScale; }
	float getYScale() { return yScale; }

private:
	int xPos, yPos, dWidth, dHeight, width, height;
	float xScale = 1.0f, yScale = 1.0f;
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer = nullptr;
};

