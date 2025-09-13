#include "GameElement.h"

#include <string>

#pragma once

class Brick : public GameElement {
private:
	static const int _width = 80, 
					 _height = 18;

	int _x, _y;
	bool _isDestroyed = false;

public:
	Brick(int x, int y) : GameElement() {
		_x = x;
		_y = y;
		unsigned int color[3] = { 255, 255, 255 };
	}

	RECT GetBounds() {
		return RECT{ _x, _y, _width, _height };
	}

	void Destroy() {
		_isDestroyed = true;
	}

	bool isDestroyed() {
		return _isDestroyed;
	}

	static int height() {
		return _height;
	}

	static int width() {
		return _width;
	}

	int x() {
		return _x;
	}

	int y() {
		return _y;
	}
};