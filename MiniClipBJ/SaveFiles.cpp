#include "SaveFiles.h"

SaveFiles::SaveFiles()
{
	loadFromFile();
}

SaveFiles::~SaveFiles() = default;


void SaveFiles::setHighScores(int hs1, int hs2, int hs5)
{
	bool aux = false;
	if(hs1 > highscore1 || hs2 > highscore2 || hs5 > highscore5) aux = true;
	highscore1 = hs1;
	highscore2 = hs2;
	highscore5 = hs5;
	if(aux) saveToFile();
}

void SaveFiles::saveToFile()
{
	std::ofstream saveFile("Assets/saveFile.txt", std::ios::trunc);
	if (saveFile.is_open())
	{
		saveFile << highscore1 << std::endl;
		saveFile << highscore2 << std::endl;
		saveFile << highscore5 << std::endl;
		saveFile << level << std::endl;
		saveFile << displayMode << std::endl;
		saveFile << width << std::endl;
		saveFile << height << std::endl;
		saveFile.close();
	}
	else std::cout << "Unable to open/create file" << std::endl;
}

void SaveFiles::loadFromFile()
{
	std::ifstream saveFile("Assets/saveFile.txt");
	if (saveFile.is_open())
	{
		int temp = 0;
		saveFile >> highscore1;
		saveFile >> highscore2;
		saveFile >> highscore5;
		saveFile >> temp;
		if(level >= 1 && level <= 10) level = temp;
		else level = 1;
		temp = 0; 
		saveFile >> temp;
		if(temp >= 0 && temp <= 3) displayMode = temp;
		else displayMode = 0;
		temp = 0;
		saveFile >> temp;
		if(temp >= 1024) width = temp;
		else width = 1024;
		temp = 0;
		if(temp >= 680) height = temp;
		else height = 680;
		saveFile >> height;
		saveFile.close();
	}
	else std::cout << "Could not find save file" << std::endl;
}
