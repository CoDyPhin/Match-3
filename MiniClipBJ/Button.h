#pragma once
#include "GameObject.h"
#include "TextObject.h"

class Button :
    public GameObject
{
public:
    Button(const char* text, int fontSize, int x = 0, int y = 0, int w = 200, int h = 100, SDL_Color textColor = { 0,0,0,255 }, SDL_Color bgColor = {192, 192, 192, 255});
	~Button();
    void Update();

    std::string getText() { return text; }

private:
    SDL_Color bgColor;
    TextObject* textObj;
    SDL_Rect rect;
    std::string text;
};
