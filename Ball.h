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

public:
	Ball();
	Ball(float x, float y, float startSpeed);
	void Move(float deltaTime);
	bool IsFell(int gameScreenHeight);

	int x() const; int y() const;
	int dx() const; int dy() const;
	int radius() const;
	int width() const;
	int height() const;
	float speed() const;
};