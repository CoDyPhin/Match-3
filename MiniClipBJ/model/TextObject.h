#pragma once
#include "../controller/GameObject.h"
class TextObject :
    public GameObject
{
public:
    TextObject(const char* fontPath, int fontSize, const char* text, SDL_Color RBGA, int startX = 0, int startY = 0);
    ~TextObject();
    void updateText(const char* newText, bool wrapped = false);

private:
    TTF_Font* font;
    SDL_Color color;
    int fontsize = 0;
    std::string text;
    bool requiresUpdate = true;
};

