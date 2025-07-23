#include <stdio.h>
#include <list>
#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "GameScreen.h"

Ball::Ball() : GameElement() {
	_ballWidth = sizeX / 3;
	_ballHeight = sizeY;
}

RECT Ball::Move(int x, int y) {
	_x0 = _x1;
	_y0 = _y1;

	_x1 += xVector;
	_y1 += yVector;

	RECT oldBall = { _x0, _y0, _x0 + width(), _y0 + height() };
	RECT newBall = { _x1, _y1, _x1 + width(), _y1 + height() };
	UnionRect(&oldBall, &oldBall, &newBall);
	return oldBall;
}

void Ball::Initialize(float startSpeed) {
	_x0 = GameScreen::halfWidth() - Ball::width() / 2;
	_y0 = GameScreen::height() - 200;
	_x1 = _x0;
	_y1 = _y0;

	_ballWidth = sizeY;
	_ballHeight = sizeY;

	_speed = startSpeed;

	xVector = _speed;
	yVector = _speed;
}

bool Ball::IsFell(int gameScreenHeight) {
	return _y1 < gameScreenHeight;
}

void Ball::CheckCollition(Platform platform, std::list<Brick> bricks) {
	CkeckWallsColliton();
	CheckPlatformCollition(platform);
	CheckBrickCollition(bricks);
}

void Ball::CkeckWallsColliton() {
	if (_x1 >= GameScreen::width() - width() * 2 || _x1 <= 0) {
		_x1 -= xVector;
		_y1 -= yVector;
		xVector = -xVector;
	}
	if (_y1 <= 0) {
		yVector = -yVector;
	}
}

void Ball::CheckPlatformCollition(Platform platform) {
	if (_y1 + height() == platform.y() &&
		_x1 + width() >= platform.currentX() && _x1 <= platform.currentX() + platform.width()) {
		yVector = -yVector;
	}

	/*if (_y1 < platform.y() && _y1 > platform.y() + platform.height() && _y1 + height() < platform.y() + platform.height() ||
		_y1 + height() < platform.y() + height() && _y1 + height() < platform.y() && _y1 < platform.y() &&
		(_x1 + width() == platform.currentX() || _x1 == platform.currentX() + platform.width())) {
		yVector = -yVector;
		xVector = -xVector;
	}*/
}

void Ball::CheckBrickCollition(std::list<Brick> bricks) {
	for (int i = 0; i < bricks.size() / sizeof(Brick); i++)
	{
		if (_y1 <= bricks)
	}
}

int Ball::lastX() { return _x0; }
int Ball::lastY() { return _y0; }

int Ball::currentX() { return _x1; }
int Ball::currentY() { return _y1; }

int Ball::width() { return _ballWidth; }
int Ball::height() { return _ballHeight; }

float Ball::speed() { return _speed; }