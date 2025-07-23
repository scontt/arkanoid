#include "GameScreen.h"
#include "Brick.h"
#include <windows.h>
#include "Drawer.h"

GameScreen::GameScreen() {}

int GameScreen::screenXbrickCount = 0;
int GameScreen::screenYbrickCount = 0;

int GameScreen::_screenHeight = 0;
int GameScreen::_screenWidth = 0;
int GameScreen::_halfHeight;
int GameScreen::_halfWidth;

GameScreen::GameScreen(int width, int height) {
	GameScreen::_screenHeight = height;
	GameScreen::_screenWidth = width;
	int a = Brick::width();

	GameScreen::screenXbrickCount = width / Brick::width();
	GameScreen::screenYbrickCount = height / Brick::height() / 3;

	GameScreen::_halfHeight = height / 2;
	GameScreen::_halfWidth = width / 2;
}

void GameScreen::Fill(HWND hWnd, HDC hdc, PAINTSTRUCT ps, std::list<Brick> bricks) {
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < GameScreen::screenYbrickCount; i++)
	{
		for (size_t j = 0; j < GameScreen::screenXbrickCount; j++)
		{
			Brick brick = Brick(i, x, y);
			Drawer::DrawBrick(hWnd, ps, hdc, brick);
			bricks.push_back(brick);
			x += Brick::width();
		}
		x = 0;
		y += Brick::height();
	}
}

int GameScreen::width() { return _screenWidth; }
int GameScreen::height() { return _screenHeight; }
int GameScreen::halfWidth() { return GameScreen::_halfWidth; }
int GameScreen::halfHeight() { return GameScreen::_halfHeight; }