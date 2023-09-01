#include "GameObject.h"

GameObject::GameObject(const char* texturePath, int startX, int startY, int w, int h)
{
	xPos = startX;
	yPos = startY;
	targetX = xPos;
	targetY = yPos;
	if (texturePath != nullptr) 
	{
		texture = IMG_LoadTexture(Renderer::renderer, texturePath);
		if (texture == nullptr) std::cout << "IMG_LoadTexture failed. Error: " << SDL_GetError() << std::endl;
		if (SDL_QueryTexture(texture, nullptr, nullptr, &dWidth, &dHeight) != 0) std::cout << "IMG_QueryTexture failed. Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		dWidth = w;
		dHeight = h;
	}
	width = dWidth;
	height = dHeight;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = width;
	destRect.h = height;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(texture);
}

void GameObject::Update()
{
	Move();
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = width;
	destRect.h = height;
	if(active) Render();
}

void GameObject::Render()
{
	SDL_RenderCopy(Renderer::renderer, texture, &srcRect, &destRect);
}

void GameObject::Translate(const int x, const int y, const int vx, const int vy)
{
	targetX += x;
	targetY += y;
	if (vx > 0) xVel = vx;
	else {
		xVel = abs(x);
		Move();
	}
	if (vy > 0) yVel = vy;
	else {
		yVel = abs(y);
		Move();
	}
}

void GameObject::Move()
{

	if (xPos < targetX)
	{
		xPos = xPos + xVel > targetX ? targetX : xPos + xVel;
	}
	else if (xPos > targetX)
	{
		xPos = xPos - xVel < targetX ? targetX : xPos - xVel;
	}
	else xVel = 0;

	if (yPos < targetY)
	{
		yPos = yPos + yVel > targetY ? targetY : yPos + yVel;
	}
	else if (yPos > targetY)
	{
		yPos = yPos - yVel < targetY ? targetY : yPos - yVel;
	}
	else yVel = 0;
}

void GameObject::setPosition(const int x, const int y)
{
	targetX = x;
	targetY = y;
	xPos = x;
	yPos = y;
}

void GameObject::Scale(const float factor)
{
	xScale = factor;
	yScale = factor;
	width = static_cast<int>(std::floor(dWidth*factor));
	height = static_cast<int>(std::floor(dHeight*factor));
}

void GameObject::Scale(const float xFactor, const float yFactor)
{
	xScale = xFactor;
	yScale = yFactor;
	width = static_cast<int>(std::floor(dWidth*xFactor));
	height = static_cast<int>(std::floor(dHeight*yFactor));
}


bool GameObject::isColliding(GameObject* other)
{
	return xPos + width > other->xPos && other->xPos + other->width > xPos && yPos + height > other->yPos && other->yPos + other->height > yPos;
}

bool GameObject::isColliding(const int x, const int y, const int w, const int h)
{
	return xPos + width > x && x + w > xPos && yPos + height > y && y + h > yPos;
}

