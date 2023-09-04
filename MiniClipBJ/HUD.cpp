#include "HUD.h"

HUD::HUD(int startX, int startY) : GameObject(nullptr, startX, startY)
{
	scoreText = new TextObject("Assets/Fonts/bst.ttf", 60, "0", {0, 0, 140, 255 }, startX, startY+100);
	textObjects.push_back(new TextObject("Assets/Fonts/bst.ttf", 80, "Score", {0, 0, 140, 255}, startX, startY));
}

HUD::~HUD()
{
	delete scoreText;
}

void HUD::UpdateHUD(int score)
{
	for (auto const text : textObjects)
	{
		text->Update();
	}
	updateScore(score);
	scoreText->Update();
}

void HUD::updateScore(int score)
{
	std::string newScore = std::to_string(score);
	scoreText->updateText(newScore.c_str());
}



