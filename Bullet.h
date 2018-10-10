#pragma once
#include "libUnicornio.h"

class Bullet
{
public:
	Bullet(string spritesheet, int x, int y, float vel);

	void setPos(int x, int y);
	void setVel(float vel);
	void setSpriteSheet(string spritesheet);
	
	Sprite getSprite();
	float getX();
	float getY();
	
	void mover();
	void desenhar();

protected:
	Sprite sprite;
	float x, y;
	float vel;
};