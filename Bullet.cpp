#include "Bullet.h"

Bullet::Bullet(string spritesheet, int x, int y, float vel)
{
	setSpriteSheet(spritesheet);
	setPos(x, y);
	setVel(vel);
}

void Bullet::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Bullet::setVel(float vel)
{
	this->vel = vel;
}

void Bullet::setSpriteSheet(string spritesheet)
{
	sprite.setSpriteSheet(spritesheet);
}

Sprite Bullet::getSprite()
{
	return sprite;
}

float Bullet::getX()
{
	return x;
}

float Bullet::getY()
{
	return y;
}

void Bullet::mover()
{
	y -= vel;
}

void Bullet::desenhar()
{
	sprite.desenhar(x, y);
}