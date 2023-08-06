#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <list>
#include "GameBase.h"
#include "Save.h"

class MainMenu
{
private:
	sf::Texture t_Title, t_newGame, t_exit,t_background,t_easy,t_hard,t_normal,t_easyP, t_hardP, t_normalP,t_Rock,t_SmallRock;

	sf::Sprite* background;
	sf::Sprite* newGame;
	sf::Sprite* exit;
	sf::Sprite* title;
	sf::Sprite* easy;
	sf::Sprite* hard;
	sf::Sprite* normal;
	sf::Sprite* easyP;
	sf::Sprite* hardP;
	sf::Sprite* normalP;

	Animation* animRockMax;
	Animation* animRock_small30;
	Animation* animRock_small15;

	std::list<GameBase*> listGameObjects;

	sf::Font font;

	Save* saveRef;

public:
	MainMenu();
	MainMenu(Save& save);
	void MainFunction(sf::RenderWindow& Window);
	bool GetClick(sf::Sprite* sp, sf::Vector2i position);

};

