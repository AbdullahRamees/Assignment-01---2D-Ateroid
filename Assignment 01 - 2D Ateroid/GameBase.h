#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"


class GameBase
{
public:

    float xLoc, yLoc, xLocOffset, yLocOffset, Radius, angle;
    bool life;
    std::string name;
    Animation anim;

    GameBase();
    GameBase(int LifeSpan);

    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);
    virtual void update() {};

    void draw(sf::RenderWindow& Window);
    virtual ~GameBase() {};
};

