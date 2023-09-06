#pragma once
#include <iostream>
#include <fstream>

class SaveFiles
{
public:
	SaveFiles();
	~SaveFiles();

	void setHighScores(int hs1, int hs2, int hs5);
	void setLevel(unsigned int lvl) { level = lvl; saveToFile(); }
	int getDisplayMode() { return displayMode; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getHighScore1() { return highscore1; }
	int getHighScore2() { return highscore2; }
	int getHighScore5() { return highscore5; }
	unsigned getLevel() { return level; }

private:
	int highscore1 = 0, highscore2 = 0, highscore5 = 0;
	int displayMode = 0, width = 1024, height = 768;
	unsigned int level = 1;
	void saveToFile();
	void loadFromFile();
};

