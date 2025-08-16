#include "GameScreen.h"
#include "Brick.h"
#include "Drawer.h"

#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <iterator>
#include <math.h>

std::vector<Point> tracePoints;

GameScreen::GameScreen() {}

GameScreen::GameScreen(int width, int height) {
	_screenHeight = height;
	_screenWidth = width;

	_halfHeight = height / 2;
	_halfWidth = width / 2;
}

void GameScreen::Initialize() {
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < _yBrickCount; i++)
	{
		for (size_t j = 0; j < _xBrickCount; j++)
		{
			Brick brick = Brick(x, y);
			_bricks[i][j] = Brick(x, y);
			x += Brick::width();
		}
		x = 0;
		y += Brick::height();
	}

	_ball = Ball(10, 10, 2.0f);
	_platform = Platform(_halfWidth, _halfHeight);
}

void GameScreen::Fill(HDC hdc, PAINTSTRUCT ps) {
	for (int i = 0; i < _yBrickCount; i++)
	{
		for (int j = 0; j < _xBrickCount; j++)
		{
			Drawer::DrawBrick(hdc, &_bricks[i][j]);
		}
	}

	Drawer::DrawBall(hdc, _ball);
	Drawer::DrawPlatform(hdc, _platform);
}

void GameScreen::Update(float deltaTime, std::vector<Point> &points) {
	_ball.Move(deltaTime);
	_platform.Move(_platformNewX - _platform.width() / 2);

	CheckCollisions(deltaTime, points);
}

void GameScreen::Clear(HWND hWnd, HDC hdc, PAINTSTRUCT ps, RECT clearRect) {
	Drawer::EraseBrick(hdc, clearRect);
}

void GameScreen::CheckCollisions(float &deltaTime, std::vector<Point> &points) {
	RECT ballBounds = _ball.GetBounds();
	RECT intersectRect;

	double len = sqrt(_ball.GetDX() * deltaTime * _ball.GetDX() * deltaTime + _ball.GetDY() * deltaTime * _ball.GetDY() * deltaTime);

	double x = (double)_ball.GetX();
	double y = (double)_ball.GetY();
	double dx = _ball.GetDX() * deltaTime / len;
	double dy = _ball.GetDY() * deltaTime / len;

	for (int k = 0; k < len; k++) {
		for (int i = 0; i < _yBrickCount; ++i) {
			for (int j = 0; j < _xBrickCount; ++j) {

				if (!_bricks[i][j].isDestroyed() && IntersectPoint(x, y, _bricks[i][j].GetBounds())) {
					_bricks[i][j].Destroy();
					dy *= -1;
				}
				x += dx;
				y += dy;

				//tracePoints
				//points.push_back(Point(x, y));

			}
		}
	}
}

bool GameScreen::IntersectPoint(double x, double y, RECT rectBounds) {
	return (x >= rectBounds.left && x < rectBounds.right &&
		y >= rectBounds.top && y < rectBounds.bottom);	
}

void GameScreen::HandleMouseMove(LPARAM key) {
	_platformNewX = GET_X_LPARAM(key);
}


int GameScreen::width() const { return this->_screenWidth; }
int GameScreen::height() const { return this->_screenHeight; }
int GameScreen::halfWidth() const { return this->_halfWidth; }
int GameScreen::halfHeight() const { return this->_halfHeight; }