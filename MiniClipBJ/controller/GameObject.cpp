#include "GameObject.h"

GameObject::GameObject(const char* texturePath, int startX, int startY, int w, int h, SDL_Texture* loadedTex, bool rV)
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
	else if (loadedTex != nullptr)
	{
		texture = loadedTex;
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
	requiresVelocity = rV;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(texture);
}

void GameObject::updateTexture(SDL_Texture* newTex)
{
	if (newTex != nullptr) {
		texture = newTex;
		if (SDL_QueryTexture(texture, nullptr, nullptr, &dWidth, &dHeight) != 0) std::cout << "IMG_QueryTexture failed. Error: " << SDL_GetError() << std::endl;
		Scale(xScale, yScale);
	}
}


void GameObject::Update()
{
	if (requiresVelocity) {
		int nMoves = (SDL_GetTicks64() - ticksSinceLastMove) / Renderer::getSpeedTime();
		for (int i = 0; i < nMoves; i++)
		{
			Move();
			ticksSinceLastMove = SDL_GetTicks64();
		}
	}
	else Move();
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = width;
	destRect.h = height;
	if(hovered)
	{
		SDL_SetRenderDrawColor(Renderer::renderer, 57, 255, 20, 255); // Green
		SDL_RenderDrawRect(Renderer::renderer, &destRect);
		hovered = false;
	}
	if(active) Render();
}

void GameObject::Render()
{
	SDL_RenderCopy(Renderer::renderer, texture, nullptr, &destRect);
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
	xVel = 0;
	yVel = 0;
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
	return xPos + width >= x && x + w >= xPos && yPos + height >= y && y + h >= yPos;
}

