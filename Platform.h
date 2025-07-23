#include "GameElement.h"

#pragma once

class Platform : public GameElement {
private:
	static int _width;
	static int _height;
	int _x1, _x0, _y;

public:

	Platform();
	void Move(int x);

	int y();
	int currentX();
	int lastX();
	int width();
	int height();
};