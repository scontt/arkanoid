#include <stdio.h>
#include <string>
#include <cstdlib>
#include <gdiplus.h>

#include "Ball.h"
#include "Point.h"
#include "Brick.h"
#include "Platform.h"
#include "GameScreen.h"
#include "BallVectorDirection.h"
#include "PlatformVectorDirection.h"

#pragma comment(lib,"gdiplus.lib")

Ball::Ball() {}

Ball::Ball(float x, float y, float startSpeed) : GameElement() {
	_width = sizeY;
	_height = sizeY;

	_x = x;
	_y = y;

	_speed = startSpeed;
}

void Ball::Move(float deltaTime) {
	_x += _dx * deltaTime;
	_y += _dy * deltaTime;
}

bool Ball::IsFell(int gameScreenHeight) {
	return _y + width() > gameScreenHeight;
}

RECT Ball::GetBounds() {
	return RECT { _x - _radius, _y - _radius, _radius * 2, _radius * 2 };
}

bool Ball::CheckBrickCollition(std::list<Brick>& bricks, int vectorSize) {
	std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		if (_y <= brick->y() + brick->height() - 1 && _y + height() >= brick->y() + 1 &&
			(_x + width() >= brick->x() && std::abs(brick->x() - _x) <= 2 ||
				(_x <= brick->x() + brick->width() && std::abs((_x + width()) - (brick->x() + brick->width())) <= 2))) {

			xVector = -xVector;

			bricks.erase(brick);
			return true;
		}

		if ((brick->y() + brick->height() == _y || brick->y() == _y + height()) &&
			_x < brick->x() + brick->width() && _x + width() > brick->x()) {

			yVector = -yVector;
			
			bricks.erase(brick);
			return true;
		}
	}
	return false;
}

int Ball::GetX() const { return _x; }
int Ball::GetY() const { return _y; }
int Ball::GetDX() const { return _dx; }
int Ball::GetDY() const { return _dy; }

int Ball::radius() const { return _radius; }
int Ball::width() const { return _width; }
int Ball::height() const { return _height; }

float Ball::speed() const { return _speed; }