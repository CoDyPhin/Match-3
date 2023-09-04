#include "TextObject.h"


TextObject::TextObject(const char* fontPath, int fontSize, const char* text, SDL_Color RBGA, int startX, int startY) : GameObject(nullptr, startX, startY, strlen(text) * 60 , fontSize, nullptr)
{
	this->fontsize = fontSize;
	this->color = RBGA;
	font = TTF_OpenFont(fontPath, fontSize);
	if (font == nullptr)
	{
		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		updateText(text);
	}
	updateTexture(texture);
	if(text != nullptr) this->text = std::string(text);
}

TextObject::~TextObject()
{
	TTF_CloseFont(font);
}

void TextObject::updateText(const char* newText)
{
	if (requiresUpdate)
	{
		std::string const aux = std::string(newText);
		text = aux;
		if (texture != nullptr) SDL_DestroyTexture(texture);
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, newText, color);
		if (textSurface == nullptr)
		{
			std::cout << "Failed to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(Renderer::renderer, textSurface);
			if (texture == nullptr)
			{
				std::cout << "Failed to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
			}
			else {
				updateTexture(texture);
				SDL_FreeSurface(textSurface);
			}
		}
	}
}
