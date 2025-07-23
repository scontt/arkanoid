#include "GameElement.h"

#pragma once

class Brick : public GameElement {
private:
	static int _brickWidth, _brickHeight;

	int _brickXcoordinate,
		_brickYcoordinate,
		_brickLevel;
public:
	Brick(int level, int x, int y);
	bool isHit();

	static int width();
	static int height();

	int x();
	int y();
};