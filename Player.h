#pragma once
#include "libUnicornio.h"
#include "Utils.h"

class Player
{
public:
public:
	Player(string spritesheet, int x, int y, float vel);

	Sprite getSprite();
	void setPos(int x, int y);
	float getX();
	float getY();
	void reload();
	bool reloaded();
	void setVel(float vel);
	void setSpriteSheet(string spritesheet);

	void mover(float* dir);
	void desenhar();

protected:
	Sprite sprite;
	float x, y;
	float vel;
	bool reloading = false;
	Timer timer;
};