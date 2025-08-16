#include <list>
#include <windows.h>
#include <stdio.h>
#include "Brick.h"
#include "Ball.h"

#pragma once

class GameScreen {
private:
	static const int _xBrickCount = 10;
	static const int _yBrickCount = 6;
	int _screenWidth, _screenHeight, _halfWidth, _halfHeight;
	int _platformNewX;

	Brick _bricks[_yBrickCount][_xBrickCount];
	Ball _ball;
	Platform _platform;

public:
	GameScreen(int width, int height);
	void Initialize();
	void Fill(HDC, PAINTSTRUCT);
	void Update(float deltaTime);
	void Clear(HWND, HDC, PAINTSTRUCT, RECT);
	void HandleMouseMove(LPARAM);
	void CheckCollisions();

	int width() const;
	int height() const;
	int halfWidth() const;
	int halfHeight() const;
};