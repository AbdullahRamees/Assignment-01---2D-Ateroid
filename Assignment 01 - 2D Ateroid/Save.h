#pragma once
#include <fstream>
using namespace std;

class Save
{
private:
	fstream SaveFile;

public:
	Save();
	void WriteScore(int Score);
	int ReadScore();
};

