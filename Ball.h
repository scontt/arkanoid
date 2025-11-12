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
public:
	int _diameter = 18;
	int _radius;
	int _x0, _y0;
	float _speed;
	float _dx, _dy;

	const int TRAIL_LENGTH = 5;


	Ball(float x, float y, float startSpeed) : GameElement() {
		_radius = _diameter / 2;

		_x0 = x;
		_y0 = y;

		_dx = 3;
		_dy = -7;

		float len = sqrt(_dx * _dx + _dy * _dy);

		_dx = _dx / len;
		_dy = _dy / len;

		_speed = 1;
		
	}


	bool IsFell(int gameScreenHeight) {
		return _y0 + diameter() > gameScreenHeight;
	}

	void ReverseX() { _dx *= -1; }
	void ReverseY() { _dy *= -1; }


	int diameter() const { return _diameter; }
	int radius() const { return _radius; }

};