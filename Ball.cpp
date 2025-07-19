#include "Ball.h"

Ball::Ball() : GameElement() {
	ballXsize = sizeX / 3;
	ballYsize = sizeY;

	unsigned int color[3] = { 255, 255, 255 };
}

void Ball::Move() {
	_x0 = _x1;
	_y0 = _y1;

	_x1 += xVector;
	_y1 += yVector;
}

void Ball::Initialize(float x0, float y0) {
	_x0 = x0;
	_y0 = y0;
	_x1 = _x0;
	_y1 = _y0;

	xVector = speed;
	yVector = speed;
}

bool Ball::IsFell(float gameScreenHeight) {
	return _y1 < gameScreenHeight;
}