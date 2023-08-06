#pragma once
#include <SFML/Graphics.hpp>
#include "Save.h"

class EndGameScreen
{
private:
	sf::Texture t_Title, t_background,t_rMainMenu;

	sf::Sprite* background;
	sf::Sprite* title;
	sf::Sprite* returnToMainmenu;

	sf::Font font;

	Save* saveRef;

public:
	EndGameScreen(Save& save);
	void EndLoop(sf::RenderWindow& Window);
};

