#include "GameElement.h"

#include <windows.h>

#pragma once

class Brick : public GameElement {
private:
	static int _width, _height;

	int _x, _y;
	bool _isDestroyed = false;
public:
	Brick();
	Brick(int x, int y);
	RECT GetBounds();
	void Destroy();

	bool isDestroyed();
	static int width();
	static int height();

	int x();
	int y();
};