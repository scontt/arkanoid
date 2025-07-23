#include "Platform.h"
#include "GameElement.h"
#include "GameScreen.h"

int Platform::_width = GameElement::sizeX;
int Platform::_height = GameElement::sizeY;

Platform::Platform() : GameElement() {
	_x0 = _x1 = GameScreen::halfWidth() - _width / 2;
	_y = GameScreen::height() - 150;
}

void Platform::Move(int x) {
	_x0 = _x1;
	_x1 = x;
}

int Platform::y() { return _y; }
int Platform::currentX() { return _x1; }
int Platform::lastX() { return _x0; }
int Platform::width() { return _width; }
int Platform::height() { return _height; }