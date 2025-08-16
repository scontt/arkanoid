#include "GameElement.h"
#include "Platform.h"
#include "Brick.h"
#include "BallVectorDirection.h"
#include "PlatformVectorDirection.h"

#include <windows.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <gdiplus.h>

#include "Point.h"

#pragma once

class Ball : public GameElement {
private:
	int _width, _height;
	int _x, _y;
	int _dx, _dy;
	int _radius;
	float _speed;
	float xVector, yVector;

	const int TRAIL_LENGTH = 5;

	void ChangeVector(BallVectorDirection, PlatformVectorDirection);

public:
	Ball();
	Ball(float x, float y, float startSpeed);

	std::vector<Point> trail;

	bool IsFell(int gameScreenHeight);
	bool CheckBrickCollition(std::list<Brick>& bricks, int);

	void Move(float deltaTime);
	void CheckPlatformCollition(Platform platform);
	void ReverseX();
	void ReverseY();
	RECT GetBounds();

	int GetX() const; int GetY() const;
	int GetDX() const; int GetDY() const;
	int radius() const;
	int width() const;
	int height() const;
	float speed() const;

	Ball operator=(const Ball& other) {
		if (this != &other) {
			_x = other._x;
			_y = other._y;
			_speed = other._speed;
		}
		return *this;
	}
};