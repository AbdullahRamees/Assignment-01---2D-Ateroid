#include "Bullet.h"
#include "Setup.h"
Bullet::Bullet()
{
	name = "bullet";
}

void Bullet::update()
{
    xLocOffset = cos(angle * degreesToRadians) * 6;
    yLocOffset = sin(angle * degreesToRadians) * 6;
    angle+=rand()%7-3; 
    xLoc += xLocOffset;
    yLoc += yLocOffset;

    if (xLoc > width || xLoc<0 || yLoc > height || yLoc < 0) life = 0;
}
