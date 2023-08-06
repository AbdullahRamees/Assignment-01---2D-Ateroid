#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class ScoreBoard
{
	

	private:
		int Score;
		sf::Font font;

	public:
		ScoreBoard();
		void IncreaseScore(int points);
		int GetScore();

		void draw(sf::RenderWindow& app);

};

