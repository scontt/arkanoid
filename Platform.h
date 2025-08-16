#include "GameElement.h"

#pragma once

class Platform : public GameElement {
private:
	int _width = 80;
	int _height = 10;
	int _x = 0, _y = 0;

public:
	Platform();
	Platform(int x, int y);
	void Move(int x);
	RECT GetBounds();

	int getY();
	int getX();
	int width();
	int height();
};