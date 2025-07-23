#include "Brick.h"
#include "Ball.h"

int Brick::_brickHeight = GameElement::sizeY;
int Brick::_brickWidth = GameElement::sizeX;

Brick::Brick(int level, int x, int y) : GameElement() {
	_brickXcoordinate = x;
	_brickYcoordinate = y;
	_brickLevel = level;
	unsigned int color[3] = { 255, 255, 255 };
}

bool Brick::isHit() {
	

	return false;
}

int Brick::height() {
	return _brickHeight;
}

int Brick::width() {
	return _brickWidth;
}

int Brick::x() {
	return _brickXcoordinate;
}

int Brick::y() {
	return _brickYcoordinate;
}