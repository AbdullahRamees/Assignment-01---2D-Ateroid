#include "Save.h"
#include <fstream>
#include <string>
#include <iostream>

Save::Save()
{
	
	SaveFile.open( "HScore.txt", ios::in | ios::out);
	if (!SaveFile) {
		cout << "Error while creating the file";
	}
	else {
		cout << "File created successfully";
		SaveFile.close();
	}
}

void Save::WriteScore(int Score)
{	
	SaveFile.open("HScore.txt", ios::in | ios::out);
	if (!SaveFile) {
		cout << " Error while creating the file ";
	}
	else {
		SaveFile << Score;
		SaveFile.close();
	}
	
}

int Save::ReadScore()
{
	string line;
	SaveFile.open("HScore.txt", ios::in | ios::out);
	if (!SaveFile) {
		cout << " Error while creating the file ";
	}
	else {
		std::getline(SaveFile, line);
		SaveFile.close();
	}
	int score = std::stoi(line);
	
	return score;
}


