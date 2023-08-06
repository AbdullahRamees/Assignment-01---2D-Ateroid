#include "MainGame.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Setup.h"
#include <random>
#include <iostream>


MainGame::MainGame()
{
    t_Ship.loadFromFile("images/spaceship.png");
    t_Background.loadFromFile("images/background.jpg");
    t_ExplosionRock.loadFromFile("images/explosions/type_C.png");
    t_Rock.loadFromFile("images/rock.png");
    t_Fire.loadFromFile("images/fire_blue.png");
    t_SmallRock.loadFromFile("images/rock_small.png");
    t_ExplosionShip.loadFromFile("images/explosions/type_B.png");

    t_Ship.setSmooth(true);
    t_Background.setSmooth(true);

    background = new Sprite(t_Background);
    animExplosion = new  Animation(t_ExplosionRock, 0, 0, 256, 256, 48, 0.5);
    animRockMax = new  Animation(t_Rock, 0, 0, 64, 64, 16, 0.2, sf::Vector2f(2, 2));
    animRock_small30 = new  Animation(t_Rock, 0, 0, 64, 64, 16, 0.2);
    animRock_small15 = new Animation(t_SmallRock, 0, 0, 64, 64, 16, 0.2);
    animBullet = new Animation(t_Fire, 0, 0, 32, 64, 16, 0.8);
    animPlayer = new Animation(t_Ship, 40, 0, 40, 40, 1, 0, sf::Vector2f(1.5, 1.5));
    animPlayer_go = new Animation(t_Ship, 40, 40, 40, 40, 1, 0, sf::Vector2f(1.5, 1.5));
    animExplosion_ship = new Animation(t_ExplosionShip, 0, 0, 192, 192, 64, 0.5);

    sBoard = new ScoreBoard();
    if (!Shootbuffer.loadFromFile("Audio/shoot.wav"))
    {
        std::cout << "failed";
    }
    

    if (!ExBuffer.loadFromFile("Audio/explosion-hit.wav"))
    {
        std::cout << "failed";
    }
    

    for (int i = 0; i < 15; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->settings(*animRock_small30, rand() % width, 0/*rand() % height*/, rand() % 360, 30);
        listGameObjects.push_back(asteroid);
    }

    player = new Player();
    player->settings(*animPlayer, width / 2, height / 2, 0, 15);
    listGameObjects.push_back(player);

    ScoreToSave = 0;
}

void MainGame::MainLoop(sf::RenderWindow& window)
{
    Music* music = new Music();
    music->openFromFile("Audio/bg sound.mp3");
    music->setVolume(50);
    music->setLoop(true);
    music->play();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();


            if (event.mouseButton.button == sf::Mouse::Left)
            {
                Bullet* bullet = new Bullet();
                bullet->settings(*animBullet, player->xLoc, player->yLoc, player->angle, 10);
                listGameObjects.push_back(bullet);
                Sound* shootsound = new Sound();
                shootsound->setVolume(30);
                shootsound->setBuffer(Shootbuffer);
                ListOfShootSound.push_back(shootsound);
                shootsound->play();
                
            }
        }


        player->angle = player->MousePositionAngle(&window) - 180;

        if (Keyboard::isKeyPressed(Keyboard::Space)) player->thrust = true;
        else {
            player->thrust = false;
        }




        for (auto objectA : listGameObjects)
            for (auto objectB : listGameObjects)
            {
                if (objectA->name == "asteroid" && objectB->name == "bullet")
                    if (isCollide(objectA, objectB))
                    {

                        objectA->life = false;
                        objectB->life = false;

                        GameBase* explosion = new GameBase();
                        explosion->settings(*animExplosion, objectA->xLoc, objectA->yLoc);
                        explosion->name = "explosion";
                        listGameObjects.push_back(explosion);

                        Sound* ExplotionSound = new Sound();
                        ExplotionSound->setVolume(30);
                        ExplotionSound->setBuffer(ExBuffer);
                        ExplotionSound->play();
                        ListOfExploionSound.push_back(ExplotionSound);
                        

                        sBoard->IncreaseScore(1);
                        ScoreToSave = sBoard->GetScore();

                        for (int i = 0; i < 2; i++)
                        {
                            if (objectA->Radius == 15) continue;
                            else if (objectA->Radius == 60) {
                                GameBase* asteroid = new Asteroid();
                                asteroid->settings(*animRock_small30, objectA->xLoc, objectA->yLoc, rand() % 360, 30);
                                listGameObjects.push_back(asteroid);

                            }
                            GameBase* asteroid = new Asteroid();
                            asteroid->settings(*animRock_small15, objectA->xLoc, objectA->yLoc, rand() % 360, 15);
                            listGameObjects.push_back(asteroid);

                        }

                    }

                if (objectA->name == "player" && objectB->name == "asteroid")
                    if (isCollide(objectA, objectB))
                    {
                        objectB->life = false;
                        GameBase* shipExplotion = new GameBase();
                        shipExplotion->settings(*animExplosion_ship, objectA->xLoc, objectA->yLoc);
                        shipExplotion->name = "explosion";       
                        listGameObjects.push_back(shipExplotion);

                        ScoreToSave = sBoard->GetScore();
                        MainSwitch = 2;
                        music->stop();
                        music->~Music();
                        window.clear();
                        return;
                    }
            }


        if (player->thrust)  player->anim = *animPlayer_go;
        else   player->anim = *animPlayer;


        for (auto Explosion : listGameObjects)
            if (Explosion->name == "explosion")
                if (Explosion->anim.isEnd()) Explosion->life = 0;

        switch (GameMode)
        {
    
        case 0 :

            if (rand() % 150 == 0)
            {
                Asteroid* asteroid = new Asteroid();
                asteroid->settings(*animRock_small30, 0, rand() % height, rand() % 120, 30);
                listGameObjects.push_back(asteroid);
            }
            break;

        case 1:

            if (rand() % 150 == 0)
            {
                Asteroid* asteroid = new Asteroid();
                asteroid->settings(*animRockMax, 0, rand() % height, rand() % 120, 60);
                listGameObjects.push_back(asteroid);
            }
            break;

        case 2:

            if (rand() % 50 == 0)
            {
                Asteroid* asteroid = new Asteroid();
                asteroid->settings(*animRockMax, 0, rand() % height, rand() % 120, 60);
                listGameObjects.push_back(asteroid);
            }
            break;

        default:
            break;
        }

        for (auto i = listGameObjects.begin(); i != listGameObjects.end();)
        {
            GameBase* gameObjects = *i;

            gameObjects->update();
            gameObjects->anim.update();

            if (gameObjects->life == false) { i = listGameObjects.erase(i); delete gameObjects; }
            else i++;
        }

        for (auto i = ListOfShootSound.begin(); i != ListOfShootSound.end();)
        {
            Sound* soundObjects = *i;

            if (soundObjects->getStatus() == Sound::Stopped) {
                i = ListOfShootSound.erase(i);
                delete soundObjects;
            }
            else i++;
        }

        for (auto i = ListOfExploionSound.begin(); i != ListOfExploionSound.end();)
        {
            Sound* soundObjects = *i;

            if (soundObjects->getStatus() == Sound::Stopped) {
                i = ListOfExploionSound.erase(i);
                delete soundObjects;
            }
            else i++;
        }

        //////draw//////
        window.draw(*background);
        for (auto gameObject : listGameObjects) gameObject->draw(window);
        sBoard->draw(window);
        window.display();
    }
}

bool MainGame::isCollide(GameBase* obj1, GameBase* obj2)
{
    /*
        collide Checking
        (b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y) < (a->R + b->R)*(a->R + b->R);

    */
    bool collide = ((obj2->xLoc - obj1->xLoc) * (obj2->xLoc - obj1->xLoc)
        + (obj2->yLoc - obj1->yLoc) * (obj2->yLoc - obj1->yLoc)) <
        (obj1->Radius + obj2->Radius) * (obj1->Radius + obj2->Radius);
    return collide;
}

bool MainGame::randomBool() {
    int number = std::rand() % 5;
    if (number == 0) {
        return true;
    }
    return false;
}
