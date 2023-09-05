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
	std::vector<Button*> buttons;
	void toggle(bool toggle);

private:
};

