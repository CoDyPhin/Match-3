#pragma once
#include "GameObject.h"
#include "Button.h"
class Menu :
    public GameObject
{
public:
	Menu(int windowWidth, int windowHeight, int score1 = 0, int score2 = 0, int score5 = 0);
	~Menu();

	void UpdateMenu();


	void setCurrentMenu(unsigned int menu) { currentMenu = menu; toggleMenu(); }
	unsigned int getCurrentMenu() { return currentMenu; }
	void setScore1(int score);
	void setScore2(int score);
	void setScore5(int score);

	void setLevel(unsigned int l) { levelStatus->updateText(std::string("Level " + std::to_string(level) + " Cleared").c_str()); this->level = l;  }

	Button* getRetry() { return retrybtn; }

	std::vector<Button*> buttons;
	void toggleMenu();


private:
	std::vector<Button*> mainMenu, playMenu, timeTrialMenu, challengesMenu;
	std::vector<TextObject*> leaderboard, timeTrialScreen;
	std::vector<TextObject*> textObjects;
	TextObject* highScore;
	TextObject* levelStatus;
	TextObject* levelFailed;
	Button* retrybtn;
	Button* mainMenuButton;
	unsigned int level = 1;

	int wW, wH;
	unsigned int currentMenu = 1;
	int score1 = 0, score2 = 0, score5 = 0;
};

