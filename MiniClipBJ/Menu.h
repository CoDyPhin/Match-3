#pragma once
#include "GameObject.h"
#include "Button.h"
class Menu :
    public GameObject
{
public:
	Menu(int windowWidth, int windowHeight);
	~Menu();

	void UpdateMenu();
	std::vector<Button*> mainMenu;
	std::vector<Button*> playMenu;
	std::vector<Button*> timeTrialMenu;
	std::vector<Button*> challengesMenu;

	std::vector<Button*> pauseMenu;
	std::vector<Button*> settingsMenu;

	void setCurrentMenu(unsigned int menu) { currentMenu = menu; toggleMenu(); }
	unsigned int getCurrentMenu() { return currentMenu; }

	std::vector<Button*> buttons;
	void toggleMenu();

private:
	unsigned int currentMenu = 1;
};

