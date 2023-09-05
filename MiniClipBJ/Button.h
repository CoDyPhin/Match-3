#pragma once
#include "GameObject.h"
#include "TextObject.h"

class Button :
    public GameObject
{
public:
    Button(const char* text, int fontSize, int x = 0, int y = 0, unsigned int nM = 0, int w = 200, int h = 100, SDL_Color textColor = { 0,0,0,255 }, SDL_Color bgColor = {192, 192, 192, 255});
	~Button();
    void Update();

    std::string getText() { return text; }
    unsigned int getNextMenu() { return nextMenu; }

private:
    SDL_Color bgColor;
    TextObject* textObj;
    SDL_Rect rect;
    std::string text;
    unsigned int nextMenu = 0;
};

