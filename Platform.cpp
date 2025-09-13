#include "Platform.h"
#include "GameElement.h"
#include "GameScreen.h"

int _width = 70;
int _height = 18;

Platform::Platform(int x, int y) : GameElement() {
	_x0 = _x1 = x;
	_y = y;
}

void Platform::Move(int x) {
	_x0 = _x1;
	_x1 = x;
}

RECT Platform::GetBounds() {
	return RECT{ _x1, _y, _width, _height };
}

int Platform::y() { return _y; }
int Platform::currentX() { return _x1; }
int Platform::lastX() { return _x0; }
int Platform::width() { return _width; }
int Platform::height() { return _height; }