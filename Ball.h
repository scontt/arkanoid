#include "GameElement.h"
#include "Platform.h"
#include "Brick.h"
#include "Point.h"

#include <windows.h>
#include <gdiplus.h>
#include <cstdlib>

#pragma comment(lib,"gdiplus.lib")

#pragma once

class Ball : public GameElement {
private:
	int _diameter = 18;
	int _radius;
	int _x, _y;
	int _dx, _dy;
	float _speed;

	const int TRAIL_LENGTH = 5;

public:
	Ball(float x, float y, float startSpeed) : GameElement() {
		_radius = _diameter / 2;

		_x = x;
		_y = y;
		_dx = x;
		_dy = y;

		_speed = startSpeed;
	}

	void Move(float deltaTime) {
		_x = _dx;
		_y = _dy;

		_dx += _speed * deltaTime;
		_dy += _speed * deltaTime;
	}

	bool IsFell(int gameScreenHeight) {
		return _y + diameter() > gameScreenHeight;
	}

	void CheckPlatformCollition(Platform platform) {
		//if (_y + diameter() == platform.y() &&
		//	_x + diameter() >= platform.currentX() && _x <= platform.currentX() + platform.width()) {
		//	yVector = -yVector;
		//}


		/*if (_y <= platform.y() + platform.height() && _y + height() >= platform.y() + 1) {

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
		}*/
	}

	void ReverseX() { _dx = -_dx; }
	void ReverseY() { _dy = -_dy; }

	//void ChangeVector(BallVectorDirection bDirection, PlatformVectorDirection pDirection) {
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

	//bool CheckBrickCollition(std::list<Brick>& bricks, int vectorSize) {
	//	std::list<Brick>::iterator brick;
	//	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	//	{
	//		if (_y <= brick->y() + brick->height() - 1 && _y + height() >= brick->y() + 1 &&
	//			(_x + width() >= brick->x() && std::abs(brick->x() - _x) <= 2 ||
	//				(_x <= brick->x() + brick->width() && std::abs((_x + width()) - (brick->x() + brick->width())) <= 2))) {

	//			xVector = -xVector;

	//			bricks.erase(brick);
	//			return true;
	//		}

	//		if ((brick->y() + brick->height() == _y || brick->y() == _y + height()) &&
	//			_x < brick->x() + brick->width() && _x + width() > brick->x()) {

	//			yVector = -yVector;

	//			bricks.erase(brick);
	//			return true;
	//		}
	//	}
	//	return false;
	//}

	int x() const { return _x; }
	int y() const { return _y; }
	int dx() const { return _dx; }
	int dy() const { return _dy; }

	int diameter() const { return _diameter; }
	int radius() const { return _radius; }

	float speed() const { return _speed; }
};