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
	
	trail.push_back(Point(_x, _y));
	if (trail.size() > TRAIL_LENGTH) trail.erase(trail.begin());
}

//void Ball::Initialize(float startSpeed) {
//	xVector = _speed;
//	yVector = _speed;
//}

bool Ball::IsFell(int gameScreenHeight) {
	return _y + width() > gameScreenHeight;
}

void Ball::CheckPlatformCollition(Platform platform) {
	if (_y + height() == platform.y() &&
		_x + width() >= platform.currentX() && _x <= platform.currentX() + platform.width()) {
		yVector = -yVector;
	}


	if (_y <= platform.y() + platform.height() && _y + height() >= platform.y() + 1) {

		if (_x + width() >= platform.currentX() && std::abs(platform.currentX() - _x) <= width()) {

			if (xVector > 0)
				ChangeVector(BallVectorDirection::left, PlatformVectorDirection::right);
			else
				ChangeVector(BallVectorDirection::right, PlatformVectorDirection::right);
		}

		if (_x <= platform.currentX() + platform.width() && std::abs((_x + width()) - (platform.currentX() + platform.width())) <= width()) {
			
			if (xVector < 0)
				ChangeVector(BallVectorDirection::right, PlatformVectorDirection::left);
			else
				ChangeVector(BallVectorDirection::left, PlatformVectorDirection::left);
		}
	}
}

RECT Ball::GetBounds() {
	return RECT { _x - _radius, _y - _radius, _radius * 2, _radius * 2 };
}

void Ball::ReverseX() { _dx = -_dx; }
void Ball::ReverseY() { _dy = -_dy; }

//void Ball::ChangeVector(BallVectorDirection bDirection, PlatformVectorDirection pDirection) {
//	yVector *= -1.0f;
//
//	if (bDirection == BallVectorDirection::right && pDirection == PlatformVectorDirection::left ||
//		bDirection == BallVectorDirection::left && pDirection == PlatformVectorDirection::right) {
//		_x1 = _x0;
//		_y1 = _y0;
//		xVector *= -1.0f;
//	}
//
//}

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