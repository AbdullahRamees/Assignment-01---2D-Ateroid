#pragma once
#include "GameBase.h"

class Player : public GameBase
{
public:
    bool thrust;
    bool Slow;

    Player();
    void update();
    
    double MousePositionAngle(sf::RenderWindow* window);
};

