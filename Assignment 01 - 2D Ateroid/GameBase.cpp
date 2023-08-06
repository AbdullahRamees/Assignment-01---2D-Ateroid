#include "GameBase.h"

GameBase::GameBase()
{
	life = 1;
}

GameBase::GameBase(int LifeSpan)
{
	life = LifeSpan;
}

void GameBase::settings(Animation& a, int X, int Y, float Angle, int radius)
{
	anim = a;
	xLoc = X; yLoc = Y;
	angle = Angle;
	Radius = radius;
}

void GameBase::draw(sf::RenderWindow& Window)
{
	anim.sprite.setPosition(xLoc, yLoc);
	anim.sprite.setRotation(angle + 90);
	Window.draw(anim.sprite);

	sf::CircleShape circle(Radius);
	circle.setFillColor(sf::Color(255, 0, 0, 170));
	circle.setPosition(xLoc, yLoc);
	circle.setOrigin(Radius, Radius);
}
