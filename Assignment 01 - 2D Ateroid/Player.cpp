#include "Player.h"
#include "Setup.h"
#include <iostream>

Player::Player()
{
	name = "player";
}

void Player::update()
{
    if (thrust)
    {
        xLocOffset += cos(angle * degreesToRadians) * 0.2;
        yLocOffset += sin(angle * degreesToRadians) * 0.2;
    }
    else if (Slow) 
    {
        xLocOffset -= cos(angle * degreesToRadians) * 0.2;
        yLocOffset -= sin(angle * degreesToRadians) * 0.2;
        xLocOffset *= 0.99;
        yLocOffset *= 0.99;
    }
    else
    {
        xLocOffset *= 0.99;
        yLocOffset *= 0.99;
    }

    int maxSpeed = 5;
    float speed = sqrt(xLocOffset * xLocOffset + yLocOffset * yLocOffset);
    if (speed > maxSpeed)
    {
        xLocOffset *= maxSpeed / speed;
        yLocOffset *= maxSpeed / speed;
    }
    else if (speed <= 0) {

        xLocOffset *= 0.99;
        yLocOffset *= 0.99;
    }

    xLoc += xLocOffset;
    yLoc += yLocOffset;

    if (xLoc >width) xLoc = 0; if (xLoc < 0) xLoc =width;
    if (yLoc > height) yLoc = 0; if (yLoc < 0) yLoc = height;
}

double Player::MousePositionAngle(sf::RenderWindow* window)
{
    int Delta_x; int Delta_y;
    double Result;
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    Delta_x = xLoc - position.x;
    Delta_y = yLoc - position.y;

    Result = atan2(Delta_y,Delta_x) * 180 / (22/7);
    //std::cout << position.x << " " << position.y << std::endl;
    //std::cout << Result << std::endl;
    return Result;
}

