#include "MainMenu.h"
#include "Setup.h"
#include <iostream>
#include "MainGame.h"
#include "Asteroid.h"
#include <list>

using namespace sf;

MainMenu::MainMenu(Save& save)
{
	t_background.loadFromFile("images/background.jpg");
	t_Title.loadFromFile("images/Logo.png");
	t_newGame.loadFromFile("images/Play.png");
	t_exit.loadFromFile("images/Exit.png");
	t_easy.loadFromFile("images/Easy.png");
	t_hard.loadFromFile("images/Hard.png");
	t_normal.loadFromFile("images/Normal.png");
	t_easyP.loadFromFile("images/Easy_Pressed.png");
	t_hardP.loadFromFile("images/Hard_pressed.png");
	t_normalP.loadFromFile("images/Normal_Pressed.png");
	t_Rock.loadFromFile("images/rock.png");
	t_SmallRock.loadFromFile("images/rock_small.png");

	animRockMax = new  Animation(t_Rock, 0, 0, 64, 64, 16, 0.2, sf::Vector2f(1.5, 1.5));
	animRock_small30 = new  Animation(t_Rock, 0, 0, 64, 64, 16, 0.2);
	animRock_small15 = new Animation(t_SmallRock, 0, 0, 64, 64, 16, 0.2);
	      
	t_background.setSmooth(true);
	
	if (!font.loadFromFile("Chopsic.ttf"))
	{
		std::cout << "Load Failed!" << std::endl;
	}

	saveRef = &save;

	background = new Sprite(t_background);

	title = new Sprite(t_Title);
	title->setPosition(width / 2 - title->getLocalBounds().width/2 , height/3);
	title->setScale(Vector2f(1, 1));

	exit =  new Sprite(t_exit);
	exit->setPosition(width/2 - exit->getLocalBounds().width / 2, height/2 + height / 10 * 1);
	exit->setScale(Vector2f(1,1));

	newGame = new Sprite(t_newGame);
	newGame->setPosition(width / 2 - newGame->getLocalBounds().width / 2, height / 2 - height / 10 * 0 );
	newGame->setScale(Vector2f(1, 1));

	easy = new Sprite(t_easy);
	easy->setPosition(width - easy->getLocalBounds().width , height / 2 + height / 30 * 0);
	easy->setScale(Vector2f(1,1));

	normal = new Sprite(t_normal);
	normal->setPosition(width - normal->getLocalBounds().width , height / 2 + height / 30 * 3);
	normal->setScale(Vector2f(1, 1));

	hard = new Sprite(t_hard);
	hard->setPosition(width - hard->getLocalBounds().width , height / 2 + height / 30 * 6);
	hard->setScale(Vector2f(1, 1));

	easyP = new Sprite(t_easyP);
	easyP->setPosition(width - easyP->getLocalBounds().width , height / 2 + height / 30 * 0);
	easyP->setScale(Vector2f(1, 1));

	normalP = new Sprite(t_normalP);
	normalP->setPosition(width - normalP->getLocalBounds().width , height / 2 + height / 30 * 3);
	normalP->setScale(Vector2f(1, 1));

	hardP = new Sprite(t_hardP);
	hardP->setPosition(width - hardP->getLocalBounds().width , height / 2 + height / 30 * 6);
	hardP->setScale(Vector2f(1, 1));

	

	for (int i = 0; i < 10; i++)
	{
		Asteroid* asteroid = new Asteroid();
		asteroid->settings(*animRock_small30, rand() % width, rand() % height, rand() % 360, 30);
		listGameObjects.push_back(asteroid);
	}

	for (int i = 0; i < 5; i++)
	{
		Asteroid* asteroid = new Asteroid();
		asteroid->settings(*animRockMax, rand() % width, rand() % height, rand() % 360, 60);
		listGameObjects.push_back(asteroid);
	}

	for (int i = 0; i < 15; i++)
	{
		Asteroid* asteroid = new Asteroid();
		asteroid->settings(*animRock_small15, rand() % width, rand() % height, rand() % 360, 15);
		listGameObjects.push_back(asteroid);
	}
	
	/*rectangle.setSize(sf::Vector2f(normal->getGlobalBounds().width ,normal->getGlobalBounds().height ));
	rectangle.setPosition(normal->getPosition());

	rectangle2.setSize(sf::Vector2f(hard->getGlobalBounds().width, normal->getGlobalBounds().height));
	rectangle2.setPosition(hard->getPosition());
	rectangle2.setFillColor(sf::Color::Cyan);*/
}

void MainMenu::MainFunction(sf::RenderWindow& Window)
{
	Music* music = new Music();
	music->openFromFile("Audio/bg.mp3");
	music->setVolume(30);
	music->setLoop(true);
	music->play();

	while (Window.isOpen())
	{
		sf::Vector2i position = sf::Mouse::getPosition(Window);
		Window.draw(*background);
		Window.draw(*title);
		Window.draw(*exit);
		Window.draw(*newGame);
		/*Window.draw(rectangle);
		Window.draw(rectangle2);*/

		std::string string = "highest score : " + std::to_string(saveRef->ReadScore() );
		sf::Text ScoreText = sf::Text(string, font, 300);
		ScoreText.setPosition(100, 100);
		ScoreText.setCharacterSize(42);
		ScoreText.setStyle(sf::Text::Bold);
		ScoreText.setFillColor(sf::Color::White);
		ScoreText.setLetterSpacing(3.f);
		ScoreText.setString(string);

		Window.draw(ScoreText);
		

		Event event;
		while (Window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				Window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape)) Window.close();

			if (event.mouseButton.button == sf::Mouse::Left) {

				if (GetClick(newGame, position))
				{
					MainSwitch = 1;
					music->stop();
					music->~Music();
					Window.clear();
					return;
				}

				else if (GetClick(exit, position))
				{
					Window.close();
					return;
				}

				
				if (GetClick(easy, position))
				{
					GameMode = 0;
				}
				else if (GetClick(normal, position))
				{
					GameMode = 1;
				}
				else if (GetClick(hard, position))
				{
					GameMode = 2;
				}

			}
		}

		if (GameMode == 0) {
			Window.draw(*easyP);
			Window.draw(*normal);
			Window.draw(*hard);
		}
		else if (GameMode == 1)
		{
			Window.draw(*easy);
			Window.draw(*normalP);
			Window.draw(*hard);
		}
		else if (GameMode == 2)
		{
			Window.draw(*easy);
			Window.draw(*normal);
			Window.draw(*hardP);
		}

		for (auto i = listGameObjects.begin(); i != listGameObjects.end();)
		{
			GameBase* gameObjects = *i;

			gameObjects->update();
			gameObjects->anim.update();

			if (gameObjects->life == false) { i = listGameObjects.erase(i); delete gameObjects; }
			else i++;
		}

		for (auto gameObject : listGameObjects) gameObject->draw(Window);
		Window.display();
	}
}

bool MainMenu::GetClick(sf::Sprite* sp, sf::Vector2i position)
{
	return (position.x >= sp->getPosition().x - sp->getGlobalBounds().width / 2
		&& position.x <= sp->getPosition().x + sp->getGlobalBounds().width / 2
		&& position.y >= sp->getPosition().y - sp->getGlobalBounds().height / 2
		&& position.y <= sp->getPosition().y + sp->getGlobalBounds().height / 2);
}




