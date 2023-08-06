#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "GameBase.h"
#include "Setup.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "ScoreBoard.h"
#include <list>
#include "MainMenu.h"
#include "MainGame.h"
#include "EndGameScreen.h"

using namespace sf; 


int main()
{

	srand(time(0));
	RenderWindow window(VideoMode(), "Asteroids!", Style::Fullscreen);
    width = window.getSize().x;
    height = window.getSize().y;
	window.setFramerateLimit(60);
	MainMenu* mainMenu = nullptr;
	MainGame* Maingame = nullptr;
	Save* save = new Save();
	MainSwitch = 0;

	mainMenu = new MainMenu(*save);
	//Maingame = new MainGame();
	EndGameScreen* EndCard = new EndGameScreen(*save);
	
	while (window.isOpen()) {
		if (MainSwitch == 0) {
			mainMenu->MainFunction(window);
		}
		else if (MainSwitch == 1) {
			Maingame = new MainGame();
			Maingame->MainLoop(window);
		}
		else if (MainSwitch == 2) {
			EndCard->EndLoop(window);
		}
	}

	
	return 0;
}

