#include "Asteroid.h"
#include "Setup.h"

Asteroid::Asteroid()
{
    xLocOffset = rand() % 8 - 4;
    yLocOffset = rand() % 8 - 4;
    name = "asteroid";
}

void Asteroid::update()
{
    xLoc += xLocOffset;
    yLoc += yLocOffset;

    if (xLoc > width) xLoc = 0;  if (xLoc < 0) xLoc = width;
    if (yLoc > height) yLoc = 0;  if (yLoc < 0) yLoc = height;
}
