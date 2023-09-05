#include "HUD.h"

HUD::HUD(int startX, int startY, int gT) : GameObject(nullptr, startX, startY)
{
	textObjects.push_back(new TextObject("Assets/Fonts/bst.ttf", 80, "Score", {0, 0, 140, 255}, startX, startY));
	scoreText = new TextObject("Assets/Fonts/bst.ttf", 60, "0", {0, 0, 140, 255 }, startX, startY+100);
	textObjects.push_back(new TextObject("Assets/Fonts/bst.ttf", 80, "Time", { 0,0,140,255 }, startX, startY+200));
	timeText = new TextObject("Assets/Fonts/bst.ttf", 60, "00:00", { 0,0,140,255 }, startX, startY + 300);
	textObjects.push_back(scoreText);
	textObjects.push_back(timeText);
	startTicks = SDL_GetTicks();
	startTiming(startTicks, gT);
}

HUD::~HUD()
{
	for (auto const text : textObjects)
	{
		delete text;
	}
	textObjects.clear();
}

void HUD::UpdateHUD(int score)
{
	updateScore(score);
	updateTime();
	for (auto const text : textObjects)
	{
		text->Update();
	}
}

void HUD::updateScore(int score)
{
	scoreText->updateText(std::to_string(score).c_str());
}

void HUD::updateTime()
{
	int aux = (SDL_GetTicks64() - startTicks) / 1000;
	if(aux != elapsedTime)
	{
		if(maxTime > 0)
		{
			elapsedTime = maxTime - aux;
		}
		else
		{
			elapsedTime = aux;
		}
		if(elapsedTime <= 0)
		{
			timeOver = true;
			elapsedTime = 0;
			return;
		}
		std::ostringstream formattedTime;
		formattedTime << std::setw(2) << std::setfill('0') << elapsedTime / 60 << ":" << std::setw(2) << std::setfill('0') << elapsedTime % 60;
		timeText->updateText(formattedTime.str().c_str());
	}
}



