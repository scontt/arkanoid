#include "GameScreen.h"
#include "Brick.h"
#include "Drawer.h"

#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <iterator>

GameScreen::GameScreen(int width, int height) {
	_screenHeight = height;
	_screenWidth = width;

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
}

void GameScreen::Draw(HDC hdc, PAINTSTRUCT ps) {
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

void GameScreen::Update(float deltaTime, std::vector<Point>& points) {
	_ball.Move(deltaTime);
	_platform.Move(_platformNewX - _platform.width() / 2);

	CheckCollisions(deltaTime, points);
}

void GameScreen::CheckCollisions(float& deltaTime, std::vector<Point>& points) {
	double len = sqrt(_ball.dx() * deltaTime * _ball.dx() * deltaTime + _ball.dy() * deltaTime * _ball.dy() * deltaTime);

	double x = (double)_ball.x();
	double y = (double)_ball.y();
	double dx = _ball.dx() * deltaTime / len;
	double dy = _ball.dy() * deltaTime / len;

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

void GameScreen::Clear(HDC hdc, PAINTSTRUCT ps) {
	/*std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		Drawer::EraseBrick(hWnd, ps, hdc, *brick);
	}*/

	//Drawer::EraseBrick(hWnd, ps, hdc, clearRect);
}

int GameScreen::width() const { return _screenWidth; }
int GameScreen::height() const { return _screenHeight; }