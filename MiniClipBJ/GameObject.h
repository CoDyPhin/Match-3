#pragma once
#include <vector>
#include <string>
#include <random>
#include <set>
#include <chrono>
#include <thread>
#include "Renderer.h"

class GameObject
{
public:
	GameObject(const char * texturePath = nullptr, int startX = 0, int startY = 0, int w = 0, int h = 0);
	~GameObject();

	void Update();
	void Render();

	//void Translate(int x = 0, int y = 0);
	void setPosition(int x = 0, int y = 0);

	void Scale(float factor);
	void Scale(float xFactor, float yFactor);

	void Translate(int x = 0, int y = 0, int vx = 0, int vy = 0);
	void Move();

	float getXScale() { return xScale; }
	float getYScale() { return yScale; }

	int getWidth() { return width; }
	int getHeight() { return height; }

	int getXPos() { return xPos; }
	int getYPos() { return yPos; }
	int getXVel() { return xVel; }
	int getYVel() { return yVel; }

	void setParent(GameObject* p) { parent = p; }
	void addChild(GameObject* c) { children.push_back(c); }
	void setActive(bool a) { active = a;}
	bool isActive() { return active; }

	bool isColliding(GameObject* other);
	bool isColliding(int x, int y, int w, int h);

protected:
	int xPos, yPos, dWidth, dHeight, width, height, targetX, targetY, xVel = 0, yVel = 0;
	float xScale = 1.0f, yScale = 1.0f;
	bool active = true;


	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect, destRect;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
};

