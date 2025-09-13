#include <list>
#include <stdio.h>
#include "Brick.h"
#include "Ball.h"
#include "Drawer.h"

#include <windows.h>
#include <windowsx.h>
#include <cmath>

#pragma once

class GameScreen {
private:
	static const int _xBrickCount = 10;
	static const int _yBrickCount = 10;
	int x = 0;
	int y = 0;
	int _screenWidth, _screenHeight, _halfWidth, _halfHeight;
	int _platformNewX;

	Brick* _bricks[_yBrickCount][_xBrickCount];
	Ball* _ball;
	Platform* _platform;

public:
	GameScreen(int width, int height) {
		_screenHeight = height;
		_screenWidth = width;

		_halfHeight = height / 2;
		_halfWidth = width / 2;

		_ball = new Ball(10, 10, 2.0f);
		_platform = new Platform(_halfWidth, _halfHeight);
		FillBricks();
	}

	void FillBricks() {
		for (size_t i = 0; i < _yBrickCount; i++)
		{
			for (size_t j = 0; j < _xBrickCount; j++)
			{
				Brick brick = Brick(x, y);
				_bricks[i][j] = new Brick(x, y);
				x += Brick::width();
			}
			x = 0;
			y += Brick::height();
		}
	}

	void DrawScreen(HDC hdc) {
		for (int i = 0; i < _yBrickCount; i++)
		{
			for (int j = 0; j < _xBrickCount; j++)
			{
				if (!_bricks[i][j]->isDestroyed())
					Drawer::DrawBrick(hdc, _bricks[i][j]);
			}
		}

		Drawer::DrawBall(hdc, *_ball);
		Drawer::DrawPlatform(hdc, *_platform);
	}

	void MovePlatform(int newPlatformX) {
		_platform->Move(_platformNewX);
	}

	void Update(HDC hdc, float deltaTime) {
		DrawScreen(hdc);

		_ball->Move(deltaTime);

		CheckCollisions(deltaTime);
	}

	void Clear(HWND hWnd, HDC hdc, PAINTSTRUCT ps, RECT clearRect) {
		/*std::list<Brick>::iterator brick;
		for (brick = bricks.begin(); brick != bricks.end(); brick++)
		{
			Drawer::EraseBrick(hWnd, ps, hdc, *brick);
		}*/

		Drawer::EraseBrick(hdc, clearRect);
	}

	void CheckCollisions(float deltaTime) {

		float s = sqrt(pow(_ball->dx(), 2) + pow(_ball->dy(), 2));

		/*if (_ball.GetX() - _ball.radius() <= 0 || _ball.GetX() + _ball.radius() >= _screenWidth) _ball.ReverseX();
		if (_ball.GetY() - _ball.radius() <= 0) _ball.ReverseY();
		if (_ball.GetY() + _ball.radius() >= _screenHeight) _ball.ReverseY();

		if (IntersectRect(&intersectRect, &ballBounds, &_platform.GetBounds())) {
			_ball.ReverseY();
		}*/

		for (int i = 0; i < _yBrickCount; ++i) {
			for (int j = 0; j < _xBrickCount; ++j) {
				if (false) {
					_bricks[i][j]->Destroy();
					_ball->ReverseY();
				}
			}
		}
	}

	void HandleMouseMove(LPARAM key) {
		_platformNewX = GET_X_LPARAM(key);
	}


	int width() const { return this->_screenWidth; }
	int height() const { return this->_screenHeight; }
	int halfWidth() const { return this->_halfWidth; }
	int halfHeight() const { return this->_halfHeight; }
};