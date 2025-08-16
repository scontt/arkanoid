#include "GameElement.h"

#pragma once

class Platform : public GameElement {
private:
	static int _width;
	static int _height;
	int _x1, _x0, _y;

public:
	Platform() {}
	Platform(int x, int y);
	void Move(int x);
	RECT GetBounds();

	int y();
	int currentX();
	int lastX();
	int width();
	int height();
};