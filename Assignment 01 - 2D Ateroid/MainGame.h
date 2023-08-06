#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "ScoreBoard.h"
#include <list>
#include "GameBase.h"
#include "Player.h"
#include "Save.h"


using namespace sf;
class MainGame
{
private:
    Texture t_Ship, t_Background, t_ExplosionRock, t_Rock, t_Fire, t_SmallRock, t_ExplosionShip;

    Animation* animExplosion;
    Animation* animRockMax;
    Animation* animRock_small30;
    Animation* animRock_small15;
    Animation* animBullet;
    Animation* animPlayer;
    Animation* animPlayer_go;
    Animation* animExplosion_ship;


    Sprite* background;
    ScoreBoard* sBoard;
    Player* player;

    std::list<GameBase*> listGameObjects;
    std::list<Sound*> ListOfShootSound;
    std::list<Sound*> ListOfExploionSound;

    SoundBuffer Shootbuffer;
    SoundBuffer ExBuffer;

   
   


public:
    MainGame();
    void MainLoop(RenderWindow& Window);
    bool isCollide(GameBase* obj1, GameBase* obj2);
    bool randomBool();

};

