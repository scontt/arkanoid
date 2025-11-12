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
	int _x0, _y0;
	int _x1, _y1;
	float _xSpeed, _ySpeed;

	const int TRAIL_LENGTH = 5;

public:
	Ball(float x, float y, float startSpeed) : GameElement() {
		_radius = _diameter / 2;

		_x0 = x;
		_y0 = y;
		_x1 = x;
		_y1 = y;

		_xSpeed = 200;
		_ySpeed = 200;
	}

	void Move(float deltaTime) {
		_x0 = _x1;
		_y0 = _y1;

		_x1 += _xSpeed * deltaTime;
		_y1 += _ySpeed * deltaTime;
	}

	bool IsFell(int gameScreenHeight) {
		return _y0 + diameter() > gameScreenHeight;
	}

	void ReverseX() { _xSpeed *= -1; }
	void ReverseY() { _ySpeed *= -1; }

	int x() const { return _x0; }
	int y() const { return _y0; }
	int x1() const { return _x1; }
	int y1() const { return _y1; }

	int diameter() const { return _diameter; }
	int radius() const { return _radius; }

	float speedX() const { return _xSpeed; }
	float speedY() const { return _ySpeed; }
};