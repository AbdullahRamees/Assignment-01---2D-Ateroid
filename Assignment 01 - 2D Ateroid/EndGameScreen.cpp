#include "EndGameScreen.h"
#include <iostream>
#include "Setup.h"

using namespace sf;

EndGameScreen::EndGameScreen(Save& save)
{
	t_background.loadFromFile("images/background.jpg");
	t_Title.loadFromFile("images/Logo.png");
	t_rMainMenu.loadFromFile("images/R_MainMenu.png");

	t_background.setSmooth(true);

	if (!font.loadFromFile("Chopsic.ttf"))
	{
		std::cout << "Load Failed!" << std::endl;
	}

	saveRef = &save;

	background = new Sprite(t_background);

	title = new Sprite(t_Title);
	title->setPosition(width / 2 - title->getLocalBounds().width/2 , height / 3);

	returnToMainmenu = new Sprite(t_rMainMenu);
	returnToMainmenu->setPosition(width / 2 - returnToMainmenu->getLocalBounds().width / 2, height - height/5);
}

void EndGameScreen::EndLoop(sf::RenderWindow& Window)
{
	

	while (Window.isOpen())
	{
		Window.draw(*background);
		Window.draw(*title);
		Window.draw(*returnToMainmenu);
		sf::Vector2i position = sf::Mouse::getPosition(Window);
		Event event;
		while (Window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				Window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape)) Window.close();

			if (event.mouseButton.button == sf::Mouse::Left) {
				if (position.x >= returnToMainmenu->getPosition().x - returnToMainmenu->getGlobalBounds().width / 2
					&& position.x <= returnToMainmenu->getPosition().x + returnToMainmenu->getGlobalBounds().width / 2
					&& position.y >= returnToMainmenu->getPosition().y - returnToMainmenu->getGlobalBounds().height / 2
					&& position.y <= returnToMainmenu->getPosition().y + returnToMainmenu->getGlobalBounds().height / 2) {
					MainSwitch = 0;
					Window.clear();
					return;
				}
			}

		}
		

		if (saveRef->ReadScore() <= ScoreToSave) {
			saveRef->WriteScore(ScoreToSave);
			std::string string = "New highest score";
			Text ScoreText = Text(string, font);
			FloatRect bounds = ScoreText.getLocalBounds();
			ScoreText.setPosition(width / 2 - bounds.width + bounds.width / 3, height /4);
			ScoreText.setCharacterSize(42);
			ScoreText.setStyle(Text::Bold);
			ScoreText.setFillColor(Color::Red);
			ScoreText.setString(string);

			Window.draw(ScoreText);
		}

		std::string string = "Your Score : " + std::to_string(ScoreToSave);
		Text ScoreText = Text(string, font);
		FloatRect bounds = ScoreText.getLocalBounds();
		ScoreText.setPosition(width / 2 - bounds.width + bounds.width/3, height / 2);
		ScoreText.setCharacterSize(42);
		ScoreText.setStyle(Text::Bold);
		ScoreText.setFillColor(Color::White);
		ScoreText.setString(string);

		Window.draw(ScoreText);
		Window.display();

	}
}
