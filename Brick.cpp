#include "Brick.h"
#include "Ball.h"

#include <string>

int Brick::_height = GameElement::sizeY;
int Brick::_width = GameElement::sizeX;

Brick::Brick() {}

Brick::Brick(int x, int y) : GameElement() {
	_x = x;
	_y = y;
	unsigned int color[3] = { 255, 255, 255 };
}

RECT Brick::GetBounds() {
	return RECT{ _x, _y, _width, _height };
}

void Brick::Destroy() {
	_isDestroyed = true;
}

bool Brick::isDestroyed() {
	return _isDestroyed;
}

int Brick::height() {
	return _height;
}

int Brick::width() {
	return _width;
}

int Brick::x() {
	return _x;
}

int Brick::y() {
	return _y;
}