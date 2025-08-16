#include "GameElement.h"

#pragma once

class Brick : public GameElement {
private:
	static int _width, _height;

	int _x, _y;
	bool _isDestroyed;

public:
	Brick();
	Brick(int x, int y);
	RECT GetBounds();
	bool isDestroyed();
	void Destroy();

	static int width();
	static int height();

	int x();
	int y();
};