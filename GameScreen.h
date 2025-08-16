#include <list>
#include <windows.h>
#include <stdio.h>
#include "Brick.h"
#include "Ball.h"

#pragma once

class GameScreen {
private:
	static const int _xBrickCount = 8;
	static const int _yBrickCount = 10;

	int _screenWidth, _screenHeight;
	int _platformNewX;

	Brick _bricks[_yBrickCount][_xBrickCount];
	Ball _ball;
	Platform _platform = Platform(400, 360);

public:
	GameScreen(int width, int height);
	void Draw(HDC, PAINTSTRUCT);
	void Clear(HDC, PAINTSTRUCT);
	void Update(float deltaTime, std::vector<Point>& points);
	bool IntersectPoint(double x, double y, RECT rectBounds);
	void HandleMouseMove(LPARAM);
	void CheckCollisions(float& deltaTime, std::vector<Point>& points);

	int width() const;
	int height() const;
};