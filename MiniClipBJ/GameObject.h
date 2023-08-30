#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <string>
#include <random>
#include <set>

class GameObject
{
public:
	GameObject(const char * texturePath = nullptr, int startX = 0, int startY = 0, int w = 0, int h = 0);
	~GameObject();

	void Update();
	void Render();

	void Translate(int x = 0, int y = 0);
	void setPosition(int x = 0, int y = 0);

	void Scale(float factor);
	void Scale(float xFactor, float yFactor);

	float getXScale() { return xScale; }
	float getYScale() { return yScale; }

	int getWidth() { return width; }
	int getHeight() { return height; }

	int getXPos() { return xPos; }
	int getYPos() { return yPos; }

	void setParent(GameObject* p) { parent = p; }
	void addChild(GameObject* c) { children.push_back(c); }

protected:
	int xPos, yPos, dWidth, dHeight, width, height;
	float xScale = 1.0f, yScale = 1.0f;
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect, destRect;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
};

