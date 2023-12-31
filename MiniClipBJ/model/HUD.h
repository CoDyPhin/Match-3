#pragma once
#include "../controller/GameObject.h"
#include "TextObject.h"

class HUD :
    public GameObject
{
public:
	HUD(int startX, int startY, int gT = 0);
	~HUD();
	void UpdateHUD(int score);
	void updateScore(int score);
	void updateTime();

	bool isTimeOver() { return timeOver; }

	void startTiming(uint64_t t, int gT = 0) { this->startTicks = t; maxTime = gT; }

private:
	std::vector<TextObject*> textObjects;
	TextObject* scoreText;
	TextObject* timeText;
	int elapsedTime = 0, maxTime = 0;
	uint64_t startTicks;
	bool timeOver = false;
};

