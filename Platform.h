#include "GameElement.h"

#pragma once

class Platform : public GameElement {
private:
	int _width = 80;
	int _height = 18;
	int _x1, _x0, _y;

public:
	Platform(int x, int y) : GameElement() {
		_x0 = _x1 = x;
		_y = y;
	}

	void Move(int x) {
		_x0 = _x1;
		_x1 = x;
	}

	RECT GetBounds() {
		return RECT{ _x1, _y, _width, _height };
	}

	int y() { return _y; }
	int currentX() { return _x1; }
	int lastX() { return _x0; }
	int width() { return _width; }
	int height() { return _height; }
};