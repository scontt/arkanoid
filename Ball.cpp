#include <stdio.h>
#include <list>
#include <string>
#include <iterator>
#include <cstdlib>

#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "GameScreen.h"
#include "BallVectorDirection.h"
#include "PlatformVectorDirection.h"

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
	return _y1 + width() > gameScreenHeight;
}

void Ball::CheckWallsColliton() {
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


	if (_y1 <= platform.y() + platform.height() && _y1 + height() >= platform.y() + 1) {

		if (_x1 + width() >= platform.currentX() && std::abs(platform.currentX() - _x1) <= width()) {

			if (xVector > 0)
				ChangeVector(BallVectorDirection::left, PlatformVectorDirection::right);
			else
				ChangeVector(BallVectorDirection::right, PlatformVectorDirection::right);
		}

		if (_x1 <= platform.currentX() + platform.width() && std::abs((_x1 + width()) - (platform.currentX() + platform.width())) <= width()) {
			
			if (xVector < 0)
				ChangeVector(BallVectorDirection::right, PlatformVectorDirection::left);
			else
				ChangeVector(BallVectorDirection::left, PlatformVectorDirection::left);
		}
	}
}

void Ball::ChangeVector(BallVectorDirection bDirection, PlatformVectorDirection pDirection) {
	yVector *= -1.0f;

	if (bDirection == BallVectorDirection::right && pDirection == PlatformVectorDirection::left ||
		bDirection == BallVectorDirection::left && pDirection == PlatformVectorDirection::right) {
		_x1 = _x0;
		_y1 = _y0;
		xVector *= -1.0f;
	}

}

bool Ball::CheckBrickCollition(std::list<Brick>& bricks, int vectorSize) {
	std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		if (_y1 <= brick->y() + brick->height() - 1 && _y1 + height() >= brick->y() + 1 &&
			(_x1 + width() >= brick->x() && std::abs(brick->x() - _x1) <= 2 ||
				(_x1 <= brick->x() + brick->width() && std::abs((_x1 + width()) - (brick->x() + brick->width())) <= 2))) {

			xVector = -xVector;

			bricks.erase(brick);
			return true;
		}

		if ((brick->y() + brick->height() == _y1 || brick->y() == _y1 + height()) &&
			_x1 < brick->x() + brick->width() && _x1 + width() > brick->x()) {

			yVector = -yVector;
			
			bricks.erase(brick);
			return true;
		}
	}
	return false;
}

int Ball::lastX() { return _x0; }
int Ball::lastY() { return _y0; }

int Ball::currentX() { return _x1; }
int Ball::currentY() { return _y1; }

int Ball::width() { return _ballWidth; }
int Ball::height() { return _ballHeight; }

float Ball::speed() { return _speed; }