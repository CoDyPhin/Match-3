#pragma once
#include "GameObject.h"
#include "TextObject.h"

class HUD :
    public GameObject
{
public:
	HUD(int startX, int startY);
	~HUD();
	void UpdateHUD(int score);
	void updateScore(int score);
private:
	std::vector<TextObject*> textObjects;
	TextObject* scoreText;
};

