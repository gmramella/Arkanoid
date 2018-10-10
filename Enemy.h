#pragma once
#include "libUnicornio.h"

class Enemy
{
public:
	Enemy(string spritesheet, int x, int y, float vel);

	void setPos(int x, int y);
	void setVel(float vel);
	void setSpriteSheet(string spritesheet);

	Sprite getSprite();
	int getAltura();
	int getLargura();
	float getX();
	float getY();
	void incX(int dx);
	void setY(int y);
	void toggleDir();

	void descer();
	void mover();
	void desenhar();

protected:
	Sprite sprite;
	float x, y;
	float vel;
	bool dir = 0;
};