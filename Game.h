#include <list>
#include <stdio.h>
#include "Brick.h"
#include "Ball.h"
#include "Drawer.h"
#include "TracePoint.h"

#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <gdiplus.h>
#include <vector>

#pragma once

#define DEBUG_LAYER TRUE

class Game {
private:
	static const int _xBrickCount = 10;
	static const int _yBrickCount = 10;
	int x = 0;
	int y = 0;
	float xs = 0.0f;
	float ys = 0.0f;
	int _screenWidth, _screenHeight, _halfWidth, _halfHeight;

	std::vector<TracePoint> _points;
	Brick* _bricks[_yBrickCount][_xBrickCount];
	Ball* _ball;
	Platform* _platform;

	Gdiplus::Bitmap* backBuffer;
	Gdiplus::Graphics* graphics;

	void ProcessPlatformMoving() {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			_platform->Move(_platform->currentX() - 7);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			_platform->Move(_platform->currentX() + 7);
		}
	}

public:
	Game(int width, int height, HWND hWnd) {
		_screenHeight = height;
		_screenWidth = width;

		_halfHeight = height / 2;
		_halfWidth = width / 2;

		_ball = new Ball(_halfWidth, _halfHeight, 100.0f);
		_platform = new Platform(_halfWidth, _halfHeight + 100);
		FillBricks();
		Initialize(hWnd);
	}

	void Initialize(HWND hWnd) {
		RECT rect;
		GetClientRect(hWnd, &rect);
		backBuffer = new Gdiplus::Bitmap(rect.right, rect.bottom);
		graphics = Gdiplus::Graphics::FromImage(backBuffer);
	}

	void Render(HWND hWnd) {
		graphics->Clear(Gdiplus::Color::Black);

		DrawScreen(*graphics);

		HDC hdc = GetDC(hWnd);
		Gdiplus::Graphics window(hdc);
		window.DrawImage(backBuffer, 0, 0);
		ReleaseDC(hWnd, hdc);
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

	void DrawScreen(Gdiplus::Graphics& g) {
		for (int i = 0; i < _yBrickCount; i++)
		{
			for (int j = 0; j < _xBrickCount; j++)
			{
				if (!_bricks[i][j]->isDestroyed())
					Drawer::DrawBrick(g, _bricks[i][j]);
			}
		}

		if (DEBUG_LAYER) {
			for (size_t i = 0; i < _points.size(); i++)
			{
				Drawer::DrawPoint(g, _points[i].x(), _points[i].y());
			}
		}

		Drawer::DrawBall(g, *_ball);
		Drawer::DrawPlatform(g, *_platform);
	}

	void Update(float deltaTime) {
		_ball->Move(deltaTime);
		ProcessPlatformMoving();
		CheckCollisions();
	}

	void CheckCollisions() {

		float s = sqrt(pow(_ball->x1() - _ball->x(), 2) + pow(_ball->y1() - _ball->y(), 2));

		for (float i = 0; i < s; i+=1.5f)
		{
			xs = _ball->x() + i / s * (_ball->x1() - _ball->x());
			ys = _ball->y() + i / s * (_ball->y1() - _ball->y());

			for (int i = 0; i < _yBrickCount; ++i) {
				for (int j = 0; j < _xBrickCount; ++j) {
					if (false) {
						_bricks[i][j]->Destroy();
						_ball->ReverseY();
					}
				}
			}
			_points.push_back(TracePoint(xs, ys));
		}

	}

	int width() const { return this->_screenWidth; }
	int height() const { return this->_screenHeight; }
	int halfWidth() const { return this->_halfWidth; }
	int halfHeight() const { return this->_halfHeight; }
	int platformX() const { return this->_platform->currentX(); }
};