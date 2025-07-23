#include <stdio.h>
#include <list>
#include <string>
#include <iterator>

#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "GameScreen.h"
#include "HitStates.h"

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

	if (_y1 <= platform.y() + platform.height() && _y1 + height() >= platform.y() &&
		((_x1 + width() >= platform.currentX() && platform.currentX() - _x1 <= width() / 3) ||
		(_x1 <= platform.currentX() + platform.width() && _x1 + width() - platform.currentX() <= width() / 3))) {
		_x1 = _x0;
		_y1 = _y0;
		yVector = -yVector;
		xVector = -xVector;
	}
}

bool Ball::CheckBrickCollition(std::list<Brick>& bricks, int vectorSize) {
	std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		if ((brick->y() + brick->height() == _y1 || brick->y() == _y1 + height()) && 
			_x1 < brick->x() + brick->width() && _x1 + width() > brick->x()) {
			yVector = -yVector;
			//xVector = -xVector;
			/*_x1 = _x0;
			_y1 = _y0;*/
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