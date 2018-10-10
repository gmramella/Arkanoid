#include "Player.h"

Player::Player(string spritesheet, int x, int y, float vel)
{
	setSpriteSheet(spritesheet);
	setPos(x, y);
	setVel(vel);
}

Sprite Player::getSprite()
{
	return sprite;
}

void Player::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}

void Player::reload()
{
	reloading = true;
	timer.reset();
}

bool Player::reloaded()
{
	long double seconds = timer.update() / 1e9;
	if (seconds > .5)
	{
		reloading = false;
	}
	return !reloading;
}

void Player::setVel(float vel)
{
	this->vel = vel;
}

void Player::mover(float* dir)
{
	x += dir[0] * vel;
	y += dir[1] * vel;

	if (x < sprite.getLargura() / 2)
		x = sprite.getLargura() / 2;
	else if (x > gJanela.getLargura() - sprite.getLargura() / 2)
		x = gJanela.getLargura() - sprite.getLargura() / 2;

	if (y < sprite.getAltura() / 2)
		y = sprite.getAltura() / 2;
	else if (y > gJanela.getAltura() - sprite.getAltura() / 2)
		y = gJanela.getAltura() - sprite.getAltura() / 2;
}

void Player::setSpriteSheet(string spritesheet)
{
	sprite.setSpriteSheet(spritesheet);
}

void Player::desenhar()
{
	sprite.desenhar(x, y);
}