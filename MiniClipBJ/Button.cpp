#include "Button.h"

Button::Button(const char* text, int fontSize, int x, int y, int w, int h, SDL_Color textColor, SDL_Color bgColor) : GameObject(nullptr, x, y, w, h)
{
	textObj = new TextObject("Assets/Fonts/bst.ttf", fontSize, text, textColor, x, y);

	textObj->setPosition(x+(w-textObj->getWidth())/2, y+(h-textObj->getHeight())/2);
	this->bgColor = bgColor;
	this->text = std::string(text);
	rect = { x, y, w, h };
	SDL_SetRenderDrawColor(Renderer::renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(Renderer::renderer, &rect);
	SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::renderer, &rect);
}

Button::~Button()
{
	delete textObj;
}

void Button::Update()
{
	if (active)
	{
		if(hovered)
		{
			SDL_SetRenderDrawColor(Renderer::renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		}
		else
		{
			SDL_SetRenderDrawColor(Renderer::renderer, bgColor.r-30, bgColor.g-30, bgColor.b-30, bgColor.a);
		}
		SDL_RenderFillRect(Renderer::renderer, &rect);
		//SDL_RenderDrawRect(Renderer::renderer, &rect);
		textObj->Update();
	}
}
