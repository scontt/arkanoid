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

//#define DEBUG_LAYER TRUE
#define DEBUG_LAYER FALSE
#define M_PI 3.14159265358979323846

class Game {
private:
	static const int _xBrickCount = 10;
	static const int _yBrickCount = 10;
	int x = 0;
	int y = 0;
	int _screenWidth, _screenHeight, _halfWidth, _halfHeight;

	std::vector<TracePoint> _points;
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
		if (!_ball->IsFell(_screenHeight)) {
			_ball->Move(deltaTime);
			CheckCollisions();
		}
		ProcessPlatformMoving();
	}

	void CheckCollisions() {
		float dx = _ball->x1() - _ball->x();
		float dy = _ball->y1() - _ball->y();
		float s = sqrt(dx * dx + dy * dy);
		float currentAngle = atan2(dy, dx);

		const int pointCount = 8;
		std::vector<std::pair<float, float>> borderPoints;

		for (int i = 0; i < pointCount; ++i) {
			float angleOffset = currentAngle - M_PI / 2 + (i * M_PI / (pointCount - 1));
			float xb = (_ball->x() + _ball->radius()) + _ball->radius() * cos(angleOffset);
			float yb = (_ball->y() + _ball->radius()) + _ball->radius() * sin(angleOffset);
			borderPoints.push_back({ xb, yb });
		}

		for (float i = 0; i < s; i += .1f) {
			for (const auto& point : borderPoints) {
				float xs = point.first + i / s * dx;
				float ys = point.second + i / s * dy;

				if (DEBUG_LAYER) {
					_points.push_back(TracePoint(xs, ys));
					if (_points.size() > 10000)
						_points.erase(_points.begin());
				}

				// коллизия платформы
				if ((ys >= _platform->y() && ys <= _platform->y() + _platform->height()) &&
					/*(xs >= _platform->currentX() && xs <= _platform->currentX() + _platform->width()) &&*/
					_ball->speedY() > 0) {

					_ball->ReverseY();
				}

				// коллизии стен
				if (xs <= .0f && _ball->speedX() < .0f) {
					_ball->ReverseX();
					return;
				}
				if (xs >= _screenWidth - 10 && _ball->speedX() > .0f) {
					_ball->ReverseX();
					return;
				}
				if (ys <= .0f && _ball->speedY() < .0f) {
					_ball->ReverseY();
					return;
				}
				if (ys >= _screenHeight && _ball->speedY() > .0f) {
					_ball->ReverseY();
					return;
				}

				//коллизии кирпичей
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
								_ball->ReverseX();
							else
								_ball->ReverseY();

							return;
						}
					}
				}
			}
		}
	}

	int width() const { return this->_screenWidth; }
	int height() const { return this->_screenHeight; }
	int halfWidth() const { return this->_halfWidth; }
	int halfHeight() const { return this->_halfHeight; }
	int platformX() const { return this->_platform->currentX(); }
};