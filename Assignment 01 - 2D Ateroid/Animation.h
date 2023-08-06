#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	float Frame, speed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;

	Animation();
	Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed);

	Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed , sf::Vector2f V);


	void update();
	bool isEnd();
};

