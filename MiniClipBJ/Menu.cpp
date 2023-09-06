#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight, int score1, int score2, int score5)
{
	wH = windowHeight;
	wW = windowWidth;

	mainMenuButton = new Button("Main Menu", 40, windowWidth / 2 - 85, 4 * windowHeight / 5 - 25, 1, 170, 50);

	mainMenu.push_back(new Button("Play", 40, windowWidth/2-100, windowHeight/4-50, 11));
	mainMenu.push_back(new Button("Highscores", 40, windowWidth / 2 - 100, 2 * windowHeight / 4 - 50, 100));
	mainMenu.push_back(new Button("Quit", 40, windowWidth / 2 - 100, 3*windowHeight/4-50));

	playMenu.push_back(new Button("Free Play", 40, windowWidth / 2 - 100, windowHeight / 5-50, 21));
	playMenu.push_back(new Button("Time Trial", 40, windowWidth / 2 - 100, 2*windowHeight / 5-50, 22));
	playMenu.push_back(new Button("Challenges", 40, windowWidth / 2 - 100, 3*windowHeight / 5-50, 23));
	playMenu.push_back(mainMenuButton);

	timeTrialMenu.push_back(new Button("1 Minute", 40, windowWidth / 2 - 100, windowHeight / 5-50, 31));
	timeTrialMenu.push_back(new Button("2 Minutes", 40, windowWidth / 2 - 100, 2*windowHeight / 5-50, 32));
	timeTrialMenu.push_back(new Button("5 Minutes", 40, windowWidth / 2 - 100, 3*windowHeight / 5-50, 33));
	timeTrialMenu.push_back(new Button("Back", 40, windowWidth / 2 - 100, 4*windowHeight / 5-50, 11));

	challengesMenu.push_back(new Button("Next Level", 40, windowWidth / 2 - 100, 2*windowHeight / 4-50, 41));
	challengesMenu.push_back(new Button("Back", 40, windowWidth / 2 - 100, 3*windowHeight / 4-50, 11));


	leaderboard.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, "Under 1 minute", { 0,0,0,255 }, windowWidth / 4, windowHeight / 5 - 50));
	leaderboard.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, "Under 2 minutes", { 0,0,0,255 }, windowWidth / 4, 2*windowHeight / 5 - 50));
	leaderboard.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, "Under 5 minutes", { 0,0,0,255 }, windowWidth / 4, 3*windowHeight / 5 - 50));

	leaderboard.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, std::to_string(score1).c_str(), { 0,0,0,255 }, 3*windowWidth / 4, windowHeight / 5 - 50));
	leaderboard.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, std::to_string(score2).c_str(), { 0,0,0,255 }, 3 * windowWidth / 4, 2*windowHeight / 5 - 50));
	leaderboard.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, std::to_string(score5).c_str(), { 0,0,0,255 }, 3 * windowWidth / 4, 3*windowHeight / 5 - 50));

	timeTrialScreen.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, "Your score", { 0,0,0,255 }, windowWidth / 4 - 100, windowHeight / 5 - 50));
	timeTrialScreen.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, "Previous Highscore", { 0,0,0,255 }, windowWidth / 4 - 100, 2*windowHeight / 5 - 50));

	timeTrialScreen.push_back(new TextObject("Assets/Fonts/bst.ttf", 40, "0", { 0,0,0,255 }, 3*windowWidth / 4 - 100, windowHeight / 5 - 50));
	highScore = new TextObject("Assets/Fonts/bst.ttf", 40, "0", { 0,0,0,255 }, 3*windowWidth / 4 - 100, 2*windowHeight / 5 - 50);
	timeTrialScreen.push_back(highScore);

	retrybtn = new Button("Retry", 40, windowWidth / 2 - 85, 3*windowHeight / 5, 0, 170, 50);

	levelStatus = new TextObject("Assets/Fonts/bst.ttf", 40, "Level 0 Cleared", { 0,0,0,255 }, windowWidth / 2 - 125, windowHeight / 4 - 50);
	levelFailed = new TextObject("Assets/Fonts/bst.ttf", 40, "Level Failed", { 0,0,0,255 }, windowWidth / 2 - 100, windowHeight / 4 - 50);

	levelGoals = new TextObject("Assets/Fonts/bst.ttf", 20, "Goals", { 0,0,0,255 }, windowWidth/2 + 350 , 20);

	toggleMenu();
}

Menu::~Menu()
{

}


void Menu::setScore1(int score)
{
	highScore->updateText(std::to_string(score1).c_str());
	timeTrialScreen[2]->updateText(std::to_string(score).c_str());
	retrybtn->setNextMenu(31);
	if (score > score1) {
		score1 = score;
		leaderboard[3]->updateText(std::to_string(score1).c_str());
	}
}

void Menu::setScore2(int score)
{
	highScore->updateText(std::to_string(score2).c_str());
	timeTrialScreen[2]->updateText(std::to_string(score).c_str());
	retrybtn->setNextMenu(32);
	if (score > score2) {
		score2 = score;
		leaderboard[4]->updateText(std::to_string(score2).c_str());
	}
}

void Menu::setScore5(int score)
{
	highScore->updateText(std::to_string(score5).c_str());
	timeTrialScreen[2]->updateText(std::to_string(score).c_str());
	retrybtn->setNextMenu(33);
	if (score > score5) {
		score5 = score;
		leaderboard[5]->updateText(std::to_string(score5).c_str());
	}
}


void Menu::UpdateMenu()
{
	for (Button* b : buttons)
	{
		b->Update();
	}
	for (TextObject* t : textObjects)
	{
		t->Update();
	}

}

void Menu::toggleMenu()
{
	textObjects = {};
	mainMenuButton->setButtonPosition(wW / 2 - 85, 4 * wH / 5 - 25);
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
			if(level != 1) textObjects = { levelStatus };
			buttons = challengesMenu;
			break;
		case 41:
			textObjects = { levelGoals };
			mainMenuButton->setButtonPosition(5, wH - 100);
			retrybtn->setButtonPosition(5, wH - 200);
			buttons = { mainMenuButton, retrybtn };
			break;
		case 100:
			buttons = { mainMenuButton };
			textObjects = leaderboard;
			break;
		case 101:
		case 102:
		case 103:
			textObjects = timeTrialScreen;
			retrybtn->setButtonPosition(wW / 2 - 85, 3 * wH / 5 - 25);
			buttons = { mainMenuButton, retrybtn };
			break;
		case 202:
			textObjects = { levelFailed };
			retrybtn->setButtonPosition(wW / 2 - 85, 2 * wH / 4 - 25);
			mainMenuButton->setButtonPosition(wW / 2 - 85, 3 * wH / 4 - 25);
			buttons = { mainMenuButton, retrybtn };
			break;
		default:
			mainMenuButton->setButtonPosition(5, wH - 100);
			retrybtn->setButtonPosition(5, wH - 200);
			buttons = { mainMenuButton, retrybtn };
			break;
	}
}