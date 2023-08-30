#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(const char* texturePath, int startX, int startY, int w, int h)
{
	xPos = startX;
	yPos = startY;
	/*xScale = scaleX;
	yScale = scaleY;*/
	if (texturePath != nullptr) 
	{
		texture = IMG_LoadTexture(Game::renderer, texturePath);
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
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = width;
	destRect.h = height;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}

void GameObject::Translate(const int x, const int y)
{
	xPos += x;
	yPos += y;
}

void GameObject::setPosition(const int x, const int y)
{
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


