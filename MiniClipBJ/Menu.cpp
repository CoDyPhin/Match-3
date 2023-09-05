#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight)
{
	buttons.push_back(new Button("Play", 50, windowWidth/2-100, windowHeight/3 - 100));
	buttons.push_back(new Button("Quit", 50, windowWidth / 2 - 100, 2*windowHeight/3 - 100));
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

void Menu::toggle(bool toggle)
{
	for (Button* b : buttons){
		b->setActive(toggle);
	}
}