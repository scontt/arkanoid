#include <list>
#include <stdio.h>
#include "Brick.h"
#include "Ball.h"
#include "Drawer.h"
#include "Point.h"

#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <gdiplus.h>
#include <vector>

#pragma once

#define DEBUG_LAYER TRUE
//#define DEBUG_LAYER FALSE
#define M_PI 3.14159265358979323846

class Game {
public:
	static const int _xBrickCount = 10;
	static const int _yBrickCount = 10;
	int x = 0;
	int y = 0;
	int _screenWidth, _screenHeight, _halfWidth, _halfHeight;

	std::vector<Point> _points;
	Brick* _bricks[_yBrickCount][_xBrickCount];
	Ball* _ball;
	Platform* _platform;

	Gdiplus::Bitmap* backBuffer;
	Gdiplus::Graphics* graphics;

	void ProcessPlatformMoving() {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			_platform->Move(_platform->currentX() - 12);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			_platform->Move(_platform->currentX() + 12);
		}
	}


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

		Drawer::DrawBall(g, *_ball);
		Drawer::DrawPlatform(g, *_platform);
		
		
	}

	void Update(float deltaTime) {
		if (!_ball->IsFell(_screenHeight)) {
			//_ball->Move(deltaTime);
			CheckCollisions(deltaTime);
		}
		ProcessPlatformMoving();
	}

	void CheckCollisions(float deltaTime) {
		float ds = deltaTime * _ball->_speed;
		float __dx = _ball->_dx* ds;
		float __dy = _ball->_dy* ds;
		float s = sqrt(__dx*__dx + __dy*__dy);

		float xs = _ball->_x0;
		float ys = _ball->_y0;

		for (float i = 0; i < s; i += 3.0f) {

			xs += _ball->_dx * ds;
			ys += _ball->_dy * ds;

			if (DEBUG_LAYER) {
				//_points.push_back(Point(xs, ys));
				Drawer::DrawPoint(*graphics, xs, ys);
			}

			if (xs <= .0f ) {
				_ball->ReverseX();
			}
			if (xs >= _screenWidth - 10 ) {
				_ball->ReverseX();
			}
			if (ys <= .0f ) {
				_ball->ReverseY();
			}
			if (ys >= _screenHeight ) {
				_ball->ReverseY();
			}

			for (int i = 0; i < _yBrickCount; ++i) {
				for (int j = 0; j < _xBrickCount; ++j) {
					if ((ys > _bricks[i][j]->y() && ys < _bricks[i][j]->y() + _bricks[i][j]->height()) &&
						(xs > _bricks[i][j]->x() && xs < _bricks[i][j]->x() + _bricks[i][j]->width()) &&
						!_bricks[i][j]->isDestroyed()) {

						_bricks[i][j]->Destroy();

						float brickCenterX = _bricks[i][j]->x() + _bricks[i][j]->width() / 2.0f;
						float brickCenterY = _bricks[i][j]->y() + _bricks[i][j]->height() / 2.0f;

						float distX = fabs(xs - brickCenterX) / (_bricks[i][j]->width() / 2.0f);
						float distY = fabs(ys - brickCenterY) / (_bricks[i][j]->height() / 2.0f);

						if (distX > distY)
						{
							_ball->ReverseX();
						}
						else
						{
							_ball->ReverseY();
						}
					}
				}
			}
		}


		_ball->_x0 = xs;
		_ball->_y0 = ys;


	}

	int width() const { return this->_screenWidth; }
	int height() const { return this->_screenHeight; }
	int halfWidth() const { return this->_halfWidth; }
	int halfHeight() const { return this->_halfHeight; }
	int platformX() const { return this->_platform->currentX(); }
};