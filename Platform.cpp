#include "Platform.h"

#include <windows.h>

Platform::Platform(int x, int y) : GameElement() {
	_x = x;
	_y = y;
}

void Platform::Move(int x) {
	_x = x;
}

RECT Platform::GetBounds() {
	return RECT{ _x, _y, _width, _height };
}

int Platform::y() { return _y; }
int Platform::x() { return _x; }
int Platform::width() { return _width; }
int Platform::height() { return _height; }