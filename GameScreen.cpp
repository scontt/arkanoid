#include "GameScreen.h"
#include "Brick.h"
#include "Drawer.h"

#include <windows.h>
#include <windowsx.h>
#include <iterator>

GameScreen::GameScreen(int width, int height) {
	_screenHeight = height;
	_screenWidth = width;

	_halfHeight = height / 2;
	_halfWidth = width / 2;
}

void GameScreen::Initialize() {
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

void GameScreen::Update(float deltaTime) {
	_ball.Move(deltaTime);
	_platform.Move(_platformNewX);

	CheckCollisions();
}

void GameScreen::Clear(HWND hWnd, HDC hdc, PAINTSTRUCT ps, RECT clearRect) {
	/*std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		Drawer::EraseBrick(hWnd, ps, hdc, *brick);
	}*/

	Drawer::EraseBrick(hdc, clearRect);
}

void GameScreen::CheckCollisions() {
	RECT ballBounds = _ball.GetBounds();
	RECT intersectRect;

	if (_ball.GetX() - _ball.radius() <= 0 || _ball.GetX() + _ball.radius() >= _screenWidth) _ball.ReverseX();
	if (_ball.GetY() - _ball.radius() <= 0) _ball.ReverseY();
	if (_ball.GetY() + _ball.radius() >= _screenHeight) _ball.ReverseY();

	if (IntersectRect(&intersectRect, &ballBounds, &_platform.GetBounds())) {
		_ball.ReverseY();
	}

	for (int i = 0; i < _yBrickCount; ++i) {
		for (int j = 0; j < _xBrickCount; ++j) {
			if (!_bricks[i][j].isDestroyed() && IntersectRect(&intersectRect, &ballBounds, &_bricks[i][j].GetBounds())) {
				_bricks[i][j].Destroy();
				_ball.ReverseY();
			}
		}
	}
}

void GameScreen::HandleMouseMove(LPARAM key) {
	_platformNewX = GET_X_LPARAM(key);
}


int GameScreen::width() const { return this->_screenWidth; }
int GameScreen::height() const { return this->_screenHeight; }
int GameScreen::halfWidth() const { return this->_halfWidth; }
int GameScreen::halfHeight() const { return this->_halfHeight; }


int x = 0;
int y = 0;