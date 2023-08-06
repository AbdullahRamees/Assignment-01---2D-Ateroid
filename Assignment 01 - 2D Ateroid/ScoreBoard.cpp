#include "ScoreBoard.h"
#include <iostream>
#include <string.h>
#include <Windows.h>

ScoreBoard::ScoreBoard()
{
	if (!font.loadFromFile("Chopsic.ttf"))
	{
		std::cout << "Load Failed!" << std::endl;
	}
	Score = 0;
}

void ScoreBoard::IncreaseScore(int points)
{
	Score += points;
}

int ScoreBoard::GetScore()
{
	return Score;
}

void ScoreBoard::draw(sf::RenderWindow& Windows)
{
	
	std::string string = "Score : " + std::to_string(GetScore());
	sf::Text ScoreText = sf::Text(string,font,300);
	ScoreText.setPosition(100,100);
	ScoreText.setCharacterSize(42);
	ScoreText.setStyle(sf::Text::Bold);
	ScoreText.setFillColor(sf::Color::White);
	ScoreText.setLetterSpacing(3.f);
	ScoreText.setString(string);
	Windows.draw(ScoreText);

}
