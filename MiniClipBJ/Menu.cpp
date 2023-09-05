#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight)
{
	mainMenu.push_back(new Button("Play", 50, windowWidth/2-100, windowHeight/3-50, 11));
	mainMenu.push_back(new Button("Quit", 50, windowWidth / 2 - 100, 2*windowHeight/3-50 - 100));

	playMenu.push_back(new Button("Free Play", 40, windowWidth / 2 - 100, windowHeight / 5-50, 21));
	playMenu.push_back(new Button("Time Trial", 40, windowWidth / 2 - 100, 2*windowHeight / 5-50, 22));
	playMenu.push_back(new Button("Challenges", 40, windowWidth / 2 - 100, 3*windowHeight / 5-50, 23));
	playMenu.push_back(new Button("Back", 40, windowWidth / 2 - 100, 4*windowHeight / 5-50, 1));

	timeTrialMenu.push_back(new Button("1 Minute", 40, windowWidth / 2 - 100, windowHeight / 5-50, 31));
	timeTrialMenu.push_back(new Button("2 Minutes", 40, windowWidth / 2 - 100, 2*windowHeight / 5-50, 32));
	timeTrialMenu.push_back(new Button("5 Minutes", 40, windowWidth / 2 - 100, 3*windowHeight / 5-50, 33));
	timeTrialMenu.push_back(new Button("Back", 40, windowWidth / 2 - 100, 4*windowHeight / 5-50, 11));

	challengesMenu.push_back(new Button("Next Level", 40, windowWidth / 2 - 100, windowHeight / 3-50, 41));
	challengesMenu.push_back(new Button("Back", 40, windowWidth / 2 - 100, 2*windowHeight / 3-50, 11));

	toggleMenu();
}

Menu::~Menu()
{

}

void Menu::UpdateMenu()
{
	for (Button* b : buttons)
	{
		b->Update();
	}
}

void Menu::toggleMenu()
{
	switch (currentMenu)
	{
		case 1:
			buttons = mainMenu;
			break;
		case 11:
			buttons = playMenu;
			break;
		case 22:
			buttons = timeTrialMenu;
			break;
		case 23:
			buttons = challengesMenu;
			break;
		default:
			buttons = {};
			break;
	}
}