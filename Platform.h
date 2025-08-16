#include "GameElement.h"

#include <windows.h>

#pragma once

class Platform : public GameElement {
private:
	int _width = 80;
	int _height = 10;
	int _x, _y;

public:

	Platform(int x, int y);
	void Move(int x);
	RECT GetBounds();

	int y();
	int x();
	int width();
	int height();
};