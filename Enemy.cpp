#include "Enemy.h"

Enemy::Enemy(string spritesheet, int x, int y, float vel)
{
	setSpriteSheet(spritesheet);
	setPos(x, y);
	setVel(vel);
}

void Enemy::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Enemy::setVel(float vel)
{
	this->vel = vel;
}

void Enemy::descer()
{
	y += vel;
}

void Enemy::mover()
{
	x += vel * (2 * dir - 1);
}

void Enemy::setSpriteSheet(string spritesheet)
{
	sprite.setSpriteSheet(spritesheet);
}

Sprite Enemy::getSprite()
{
	return sprite;
}

int Enemy::getAltura()
{
	return sprite.getAltura();
}

int Enemy::getLargura()
{
	return sprite.getLargura();
}

float Enemy::getX()
{
	return x;
}

float Enemy::getY()
{
	return y;
}

void Enemy::incX(int dx)
{
	this->x += dx;
}

void Enemy::setY(int y)
{
	this->y = y;
}

void Enemy::toggleDir()
{
	dir = !dir;
}

void Enemy::desenhar()
{
	sprite.desenhar(x, y);
}